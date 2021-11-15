#include "stdafx.h"
#include "Material.h"
#include "texture.h"
#include "Shader.h"
#include "Graphics.h"
#include "assetManager.h"
#include "rapidjson\include\rapidjson\rapidjson.h"
#include "rapidjson\include\rapidjson\document.h"
#include "jsonUtil.h"
#include <fstream>
#include <sstream>

Material::Material()
{
	myGraphics = Graphics::Get();
	myBuffer = myGraphics->CreateGraphicsBuffer
	(&perMaterialConstant, sizeof(perMaterialConstant), D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE, D3D11_USAGE_DYNAMIC);
}

Material::~Material()
{
	myBuffer->Release();
}

void Material::SetActive() const
{
	myShader->SetActive();
	for (int i = 0; i < Graphics::TEXTURE_SLOT_TOTAL; i++)
	{
		myTextureArray[i]->SetActive(i);
	}

	myGraphics->UploadBuffer(myBuffer, &perMaterialConstant, sizeof(perMaterialConstant));
	myGraphics->GetDeviceContext()->PSSetConstantBuffers(Graphics::CONSTANT_BUFFER_MATERIAL, 1, &myBuffer);
}

void Material::SetShader(const Shader* shader)
{
	myShader = shader;
}

void Material::SetTexture(int slot, const Texture* texture)
{
	myTextureArray[slot] = texture;
}

void Material::SetDiffuseColor(const Vector3& color)
{
	perMaterialConstant.diffuseColor = color;
}

void Material::SetSpecularColor(const Vector3& color)
{
	perMaterialConstant.specularColor = color;
}

void Material::SetSpecularPower(float power)
{
	perMaterialConstant.specularPower = power;
}

Material* Material::StaticLoad(const WCHAR* fileName, AssetManager* pManager)
{
	Material* pMat = new Material();
	if (pMat->Load(fileName, pManager) == false)
	{
		delete pMat;
		return new Material();
	}
	return pMat;
}

bool Material::Load(const WCHAR* fileName, AssetManager* pAssetManager)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		return false;
	}

	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	if (!doc.IsObject())
	{
		DbgAssert(false, "Unable to open Material file");
		return false;
	}

	std::string str = doc["metadata"]["type"].GetString();
	int ver = doc["metadata"]["version"].GetInt();

	// Check the metadata
	if (!doc["metadata"].IsObject() ||
		str != "itpmat" ||
		ver != 1)
	{
		DbgAssert(false, "Mesh File Incorrect Version");
		return false;
	}

	// Load Shader
	std::wstring shaderName;
	GetWStringFromJSON(doc, "shader", shaderName);
	if (pAssetManager->GetShader(shaderName) == nullptr)
	{
		pAssetManager->SetShader(shaderName, new Shader());
	}
	SetShader(pAssetManager->GetShader(shaderName));

	// Read the textures
	const rapidjson::Value& texturesJson = doc["textures"];
	if (!texturesJson.IsArray() || texturesJson.Size() < 1)
	{
		DbgAssert(false, "Mesh File Invalid Textures");
		return false;
	}
	for (rapidjson::SizeType i = 0; i < texturesJson.Size(); i++)
	{
		std::string s = texturesJson[i].GetString();
		std::wstring ws;
		ws.assign(s.begin(), s.end());
		SetTexture(Graphics::TEXTURE_SLOT_DIFFUSE, pAssetManager->LoadTexture(ws));
	}

	Vector3 diffuseColorVec = Vector3::Zero;
	Vector3 specularColorVec = Vector3::Zero;
	float specularPower = 0.0f;
	if (GetVectorFromJSON(doc, "diffuseColor", diffuseColorVec))
	{
		SetDiffuseColor(diffuseColorVec);
	}

	if (GetVectorFromJSON(doc, "specularColor", specularColorVec))
	{
		// Load in the specular
		SetSpecularColor(specularColorVec);
	}

	if (GetFloatFromJSON(doc, "specularPower", specularPower))
	{
		// Load in the specularPower
		SetSpecularPower(specularPower);
	}

	return true;	// everything went fine
}
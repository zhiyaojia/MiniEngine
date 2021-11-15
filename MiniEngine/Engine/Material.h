#pragma once
#include "engineMath.h"
#include "Graphics.h"
#include "Shader.h"
#include "texture.h"

struct PerMaterial
{
	PerMaterial()
	{
		diffuseColor = Vector3::Zero;
		padding1 = 0.0f;
		specularColor = Vector3::Zero;
		specularPower = 0.0f;
	}
	Vector3 diffuseColor;
	float padding1;
	Vector3 specularColor;
	float specularPower;
};

class Material
{
public:
	Material();
	~Material();
	void SetActive() const;
	void SetShader(const Shader* shader);
	void SetTexture(int slot, const Texture* texture);
	void SetDiffuseColor(const Vector3& color);
	void SetSpecularColor(const Vector3& color);
	void SetSpecularPower(float power);

	bool Load(const WCHAR* fileName, AssetManager* pAssetManager);
	static Material* StaticLoad(const WCHAR* fileName, AssetManager* pManager);

	PerMaterial perMaterialConstant;

private:
	Graphics* myGraphics;
	ID3D11Buffer* myBuffer = nullptr;
	const Shader* myShader = nullptr;
	const Texture* myTextureArray[Graphics::TEXTURE_SLOT_TOTAL];
};

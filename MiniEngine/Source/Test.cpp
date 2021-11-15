#include "stdafx.h"
//#include "Camera.h"
//#include "engineMath.h"
//#include "Graphics.h"
//#include "jsonUtil.h"
//#include "Profiler.h"
//#include "RenderCube.h"
//#include "Shader.h"
//#include "SkinnedObj.h"
//#include "stringUtil.h"
//#include "texture.h"
//#include "VertexBuffer.h"
//#include "VertexFormats.h"
//#include "rapidjson\include\rapidjson\rapidjson.h"
//#include "rapidjson\include\rapidjson\document.h"
//#include "Components\Character.h"
//#include "Components\CollisionComponent.h"
//#include "Components\FollowCam.h"
//#include "Components\ParticleEmitter.h"
//#include "Components\Player.h"
//#include "Components\PointLight.h"
//#include <fstream>
//#include <sstream>
//#include "Test.h"
//
//Test::Test()
//{
//}
//
//Test::~Test()
//{
//}
//
//void Test::Init(HWND hWnd, float width, float height)
//{
//	mGraphic.InitD3D(hWnd, width, height);
//
//	InitShader();
//
//	LoadLevel(L"Assets/Levels/Level06.itplevel");
//}
//
//void Test::InitShader()
//{
//	{   // load the Simple shader
//		D3D11_INPUT_ELEMENT_DESC inputElem[] =
//		{
//			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, offsetof(VertexFormat::VertexPosColor, pos),   D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(VertexFormat::VertexPosColor, color), D3D11_INPUT_PER_VERTEX_DATA, 0 }
//		};
//		Shader* pShader = new Shader();
//		pShader->Load(L"Shaders/Mesh.hlsl", inputElem, ARRAY_SIZE(inputElem));
//		mAssetManager.SetShader(L"Mesh", pShader);
//	}
//
//	{   // load the BasicMesh shader
//		D3D11_INPUT_ELEMENT_DESC inputElem[] =
//		{
//			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, offsetof(VertexFormat::VertexPosNormalColorUV, pos),   D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, offsetof(VertexFormat::VertexPosNormalColorUV, norm),  D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(VertexFormat::VertexPosNormalColorUV, color), D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, offsetof(VertexFormat::VertexPosNormalColorUV, uv),    D3D11_INPUT_PER_VERTEX_DATA, 0 }
//		};
//		Shader* pShader = new Shader();
//		pShader->Load(L"Shaders/BasicMesh.hlsl", inputElem, ARRAY_SIZE(inputElem));
//		mAssetManager.SetShader(L"BasicMesh", pShader);
//	}
//	{   // load the Phong and Unlit shaders
//		D3D11_INPUT_ELEMENT_DESC inputElem[] =
//		{
//			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, offsetof(VertexFormat::VertexPosNormalUV, pos),   D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, offsetof(VertexFormat::VertexPosNormalUV, norm),  D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, offsetof(VertexFormat::VertexPosNormalUV, uv),    D3D11_INPUT_PER_VERTEX_DATA, 0 }
//		};
//		Shader* pShader = new Shader();
//		pShader->Load(L"Shaders/Phong.hlsl", inputElem, ARRAY_SIZE(inputElem));
//		mAssetManager.SetShader(L"Phong", pShader);
//		pShader = new Shader();
//		pShader->Load(L"Shaders/Unlit.hlsl", inputElem, ARRAY_SIZE(inputElem));
//		mAssetManager.SetShader(L"Unlit", pShader);
//	}
//	{   // load the Skinned shader
//		D3D11_INPUT_ELEMENT_DESC inputElem[] =
//		{
//			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, offsetof(VertexFormat::VertexPosNormSkinUV, pos),         D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, offsetof(VertexFormat::VertexPosNormSkinUV, norm),        D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			{ "BONE",     0, DXGI_FORMAT_R8G8B8A8_UINT,      0, offsetof(VertexFormat::VertexPosNormSkinUV, boneIndex),   D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			{ "WEIGHT",   0, DXGI_FORMAT_R8G8B8A8_UNORM,     0, offsetof(VertexFormat::VertexPosNormSkinUV, boneWeight),  D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, offsetof(VertexFormat::VertexPosNormSkinUV, uv),          D3D11_INPUT_PER_VERTEX_DATA, 0 }
//		};
//		Shader* pShader = new Shader();
//		pShader->Load(L"Shaders/Skinned.hlsl", inputElem, ARRAY_SIZE(inputElem));
//		mAssetManager.SetShader(L"Skinned", pShader);
//	}
//	{   // load the Particle shader
//		D3D11_INPUT_ELEMENT_DESC inputElem[] =
//		{
//			{ "POSITION",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexFormat::VertexPosUV, pos),                               D3D11_INPUT_PER_VERTEX_DATA,    0 },
//			{ "TEXCOORD",   0, DXGI_FORMAT_R32G32_FLOAT,    0, offsetof(VertexFormat::VertexPosUV, uv),                                D3D11_INPUT_PER_VERTEX_DATA,    0 },
//			{ "POSITION",   1, DXGI_FORMAT_R32G32B32_FLOAT, 1, offsetof(ParticleEmitter::PerParticleRenderData, pos),    D3D11_INPUT_PER_INSTANCE_DATA,  1 },
//			{ "SIZE",       0, DXGI_FORMAT_R32_FLOAT,       1, offsetof(ParticleEmitter::PerParticleRenderData, size),   D3D11_INPUT_PER_INSTANCE_DATA,  1 },
//			{ "ALPHA",      0, DXGI_FORMAT_R32_FLOAT,       1, offsetof(ParticleEmitter::PerParticleRenderData, alpha),  D3D11_INPUT_PER_INSTANCE_DATA,  1 }
//		};
//		Shader* pShader = new Shader();
//		pShader->Load(L"Shaders/Particle.hlsl", inputElem, ARRAY_SIZE(inputElem));
//		mAssetManager.SetShader(L"Particle", pShader);
//	}
//}
//
//void Test::Shutdown()
//{
//	mLightBuffer->Release();
//	for (int i = 0; i < Light::numPointLight; i++)
//	{
//		FreeLight(&mLightConst.pointLightArray[i]);
//	}
//
//	delete mCamera;
//
//	delete mRenderer;
//	delete mCube;
//
//	delete mShader;
//	delete mBasicShader;
//
//	mAssetManager.Clear();
//
//	mGraphic.CleanD3D();
//}
//
//float mRotation = 45.0f;
//void Test::Update(float deltaTime)
//{
//	mRotation += Math::Pi * deltaTime;
//	mRenderer->mObjectData.modelToWorld = Matrix4::CreateRotationZ((mRotation));
//	mRenderer->mObjectData.modelToWorld *= Matrix4::CreateScale(300.0f);
//
//	mCube->mObjectData.modelToWorld = Matrix4::CreateScale(100.0f) * Matrix4::CreateRotationY(mRotation) * Matrix4::CreateRotationX(0.25f * mRotation);
//}
//
//void Test::RenderFrame()
//{
//	mGraphic.BeginFrame(Graphics::Color4(0.0f, 0.2f, 0.4f, 1.0f));
//
//	mCamera->SetActive();
//
//	mGraphic.UploadBuffer(mLightBuffer, &mLightConst, sizeof(mLightConst));
//	mGraphic.GetDeviceContext()->PSSetConstantBuffers(mGraphic.CONSTANT_BUFFER_LIGHTING, 1, &mLightBuffer);
//
//	mRenderer->Draw();
//
//	mCube->Draw();
//
//	mGraphic.EndFrame(0, 0);
//}
//
//void Test::OnKeyDown(uint32_t key)
//{
//	m_keyIsHeld[key] = true;
//}
//
//void Test::OnKeyUp(uint32_t key)
//{
//	m_keyIsHeld[key] = false;
//}
//
//bool Test::IsKeyHeld(uint32_t key) const
//{
//	const auto find = m_keyIsHeld.find(key);
//	if (find != m_keyIsHeld.end())
//		return find->second;
//	return false;
//}
//
//Light::PointLightData* Test::AllocateLight()
//{
//	for (int i = 0; i < Light::numPointLight; i++)
//	{
//		if (!mLightConst.pointLightArray[i].isEnabled)
//		{
//			mLightConst.pointLightArray[i].isEnabled = true;
//			return &(mLightConst.pointLightArray[i]);
//		}
//	}
//	return nullptr;
//}
//
//void Test::FreeLight(Light::PointLightData* pLight)
//{
//	pLight->isEnabled = false;
//}
//
//void Test::SetAmbientLight(const Vector3& color)
//{
//	mLightConst.ambientLight = color;
//}
//
//const Vector3& Test::GetAmbientLight() const
//{
//	return mLightConst.ambientLight;
//}
//
//bool Test::LoadLevel(const WCHAR* fileName)
//{
//	//std::ifstream file(fileName);
//	//if (!file.is_open())
//	//{
//	//	return false;
//	//}
//
//	//std::stringstream fileStream;
//	//fileStream << file.rdbuf();
//	//std::string contents = fileStream.str();
//	//rapidjson::StringStream jsonStr(contents.c_str());
//	//rapidjson::Document doc;
//	//doc.ParseStream(jsonStr);
//
//	//if (!doc.IsObject())
//	//{
//	//	return false;
//	//}
//
//	//std::string str = doc["metadata"]["type"].GetString();
//	//int ver = doc["metadata"]["version"].GetInt();
//
//	//// Check the metadata
//	//if (!doc["metadata"].IsObject() ||
//	//	str != "itplevel" ||
//	//	ver != 2)
//	//{
//	//	return false;
//	//}
//
//	//{ // Read the camera data
//	//	const rapidjson::Value& camObj = doc["camera"];
//	//	if (camObj.IsObject())
//	//	{
//	//		Vector3 pos = Vector3::Zero;
//	//		GetVectorFromJSON(camObj, "position", pos);
//	//		Quaternion rot = Quaternion::Identity;
//	//		GetQuaternionFromJSON(camObj, "rotation", rot);
//	//		mCamera->mView = Matrix4::CreateFromQuaternion(rot) * Matrix4::CreateTranslation(pos);
//	//		mCamera->mView.Invert();
//	//	}
//	//}
//
//	//{ // Read the lighting data
//	//	const rapidjson::Value& lightObj = doc["lightingData"];
//	//	if (lightObj.IsObject())
//	//	{
//	//		Vector3 ambient;
//	//		GetVectorFromJSON(lightObj, "ambient", ambient);
//	//		SetAmbientLight(ambient);
//	//	}
//	//}
//
//	//{   // Load the RenderObjs
//	//	const rapidjson::Value& renderObjects = doc["renderObjects"];
//	//	if (renderObjects.IsArray())
//	//	{
//	//		for (rapidjson::SizeType i = 0; i < renderObjects.Size(); ++i)
//	//		{
//	//			const rapidjson::Value& obj = renderObjects[i];
//	//			Vector3 pos;
//	//			GetVectorFromJSON(obj, "position", pos);
//	//			Quaternion rot;
//	//			GetQuaternionFromJSON(obj, "rotation", rot);
//	//			float scale;
//	//			GetFloatFromJSON(obj, "scale", scale);
//	//			std::wstring mesh;
//	//			GetWStringFromJSON(obj, "mesh", mesh);
//	//			Mesh* pMesh = mAssetManager.LoadMesh(mesh);
//	//			RenderObj* pObj = nullptr;
//	//			SkinnedObj* pSkin = nullptr;
//	//			if ((nullptr != pMesh) && (pMesh->IsSkinned()))
//	//			{
//	//				pSkin = new SkinnedObj(&mGraphic, pMesh);
//	//				pObj = pSkin;
//	//			}
//	//			else
//	//			{
//	//				pObj = new RenderObj(pMesh);
//	//			}
//	//			pObj->mObjectData.modelToWorld =
//	//				Matrix4::CreateScale(scale)
//	//				* Matrix4::CreateFromQuaternion(rot)
//	//				* Matrix4::CreateTranslation(pos);
//
//	//			const rapidjson::Value& components = obj["components"];
//	//			if (components.IsArray())
//	//			{
//	//				for (rapidjson::SizeType j = 0; j < components.Size(); ++j)
//	//				{
//	//					Component* pComp = nullptr;
//	//					const rapidjson::Value& comp = components[j];
//	//					std::string type;
//	//					GetStringFromJSON(comp, "type", type);
//	//					if (type == "PointLight")
//	//					{
//	//						pComp = new PointLight(this, pObj);
//	//					}
//	//					else if (type == "Character")
//	//					{
//	//						pComp = new Character(this, pSkin);
//	//					}
//	//					else if (type == "Player")
//	//					{
//	//						pComp = new Player(this, pSkin);
//	//					}
//	//					else if (type == "FollowCam")
//	//					{
//	//						pComp = new FollowCam(this, pObj);
//	//					}
//	//					else if (type == "Collision")
//	//					{
//	//						pComp = new CollisionComponent(&mPhysics, pObj);
//	//					}
//	//					else if (type == "Particle")
//	//					{
//	//						pComp = new ParticleEmitter(pObj);
//	//					}
//	//					if (pComp)
//	//					{
//	//						pComp->LoadProperties(comp);
//	//						pObj->AddComponent(pComp);
//	//					}
//	//				}
//	//			}
//
//	//			mRenderObj.push_back(pObj);
//	//		}
//	//	}
//	//}
//
//	return true;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//

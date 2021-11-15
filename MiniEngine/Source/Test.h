#pragma once
#include "assetManager.h"
#include "Graphics.h"
#include "engineMath.h"
#include "Light.h"

class Shader;

class Test
{
public:
	Test();
	~Test();

//	void Init(HWND hWnd, float width, float height);
//	void Shutdown();
//	void Update(float deltaTime);
//	void RenderFrame();
//
//	void OnKeyDown(uint32_t key);
//	void OnKeyUp(uint32_t key);
//	bool IsKeyHeld(uint32_t key) const;
//
//	void InitShader();
//
//	Light::PointLightData* AllocateLight();
//	void FreeLight(Light::PointLightData* pLight);
//	void SetAmbientLight(const Vector3& color);
//	const Vector3& GetAmbientLight() const;
//
//private:
//	std::unordered_map<uint32_t, bool> m_keyIsHeld;
//	// TODO Lab 02b
//	Graphics mGraphic;
//
//	// TODO Lab 02f
//	Shader* mShader = nullptr;
//	Shader* mBasicShader = nullptr;
//
//	class RenderObj* mRenderer = nullptr;
//	class RenderObj* mCube = nullptr;
//
//	class Camera* mCamera = nullptr;
//	AssetManager mAssetManager;
//
//	Light::LightingConstant mLightConst;
//	ID3D11Buffer* mLightBuffer = nullptr;
//
//	bool LoadLevel(const WCHAR* fileName);
};
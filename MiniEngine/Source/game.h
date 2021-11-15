#pragma once
#include "assetManager.h"
#include "Graphics.h"
#include "Job.h"
#include "Physics.h"
#include "Light.h"

class Camera;
class RenderObj;
class Shader;
class Texture;

class Game
{
public:
    Game();
    ~Game();

    void Init(HWND hWnd, float width, float height);
    void Shutdown();
	void Update(float deltaTime);
    void RenderFrame();

	void OnKeyDown(uint32_t key);
	void OnKeyUp(uint32_t key);
	bool IsKeyHeld(uint32_t key) const;

    Light::PointLightData* AllocateLight();
    void FreeLight(Light::PointLightData* pLight);
    void SetAmbientLight(const Vector3& color);
    const Vector3& GetAmbientLight() const;

    AssetManager* GetAssetManager() { return &mAssetManager; }

    void AddJob(JobManager::Job* pJob) { mJobs.AddJob(pJob); }

    Camera* GetCamera() { return mCamera; }
    Physics* GetPhysics() { return &mPhysics; }

private:
	std::unordered_map<uint32_t, bool> m_keyIsHeld;
    Graphics mGraphic;
    JobManager mJobs;
    Physics mPhysics;

    Camera* mCamera;
    AssetManager mAssetManager;

    std::vector<RenderObj*> mRenderObj;

    // lighting data
    Light::LightingConstant mLightData;
    ID3D11Buffer* mLightBuffer = nullptr;

	bool LoadLevel(const WCHAR* fileName);
};
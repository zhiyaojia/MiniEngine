#include "stdafx.h"
#include "game.h"
#include "Camera.h"
#include "engineMath.h"
#include "Graphics.h"
#include "jsonUtil.h"
#include "Shader.h"
#include "SkinnedObj.h"
#include "stringUtil.h"
#include "rapidjson\include\rapidjson\rapidjson.h"
#include "rapidjson\include\rapidjson\document.h"
#include "Components\Character.h"
#include "Components\CollisionComponent.h"
#include "Components\followCam.h"
#include "Components\ParticleEmitter.h"
#include "Components\player.h"
#include "Components\PointLight.h"
#include <fstream>
#include <sstream>

Game::Game(): mGraphic(Graphics()), mCamera(nullptr), mAssetManager(AssetManager())
{
	mJobs.Begin();
}

Game::~Game()
{
}

void Game::Init(HWND hWnd, float width, float height)
{
    mGraphic.InitD3D(hWnd, width, height);

    Shader::LoadAllShader(&mAssetManager);

    mCamera = new Camera(&mGraphic);
    mLightBuffer = mGraphic.CreateGraphicsBuffer
		(&mLightData, sizeof(mLightData), D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE, D3D11_USAGE_DYNAMIC);

    LoadLevel(L"Assets/Levels/Level08.itplevel");
}

void Game::Shutdown()
{
    mJobs.End();

    //ParticleEmitter::Shutdown();

    delete mCamera;
    for (RenderObj* pObj : mRenderObj)
        delete pObj;

    mLightBuffer->Release();

    mAssetManager.Clear();

    mGraphic.CleanD3D();
}

void Game::Update(float deltaTime)
{
    for (RenderObj* pObj : mRenderObj)
        pObj->Update(deltaTime);

    {
        //PROFILE_SCOPE(WaitForJobs);
        mJobs.WaitForJobs();
    }
}

void Game::RenderFrame()
{
    {
        //PROFILE_SCOPE(BeginFrame);
        // Clear the screen to blue
        Graphics::Color4 clearColor(0.0f, 0.2f, 0.4f, 1.0f);
        mGraphic.BeginFrame(clearColor);
    }

    mCamera->SetActive();

    {
        //PROFILE_SCOPE(SetLighting);
        mGraphic.UploadBuffer(mLightBuffer, &mLightData, sizeof(mLightData));
        mGraphic.GetDeviceContext()->PSSetConstantBuffers(Graphics::CONSTANT_BUFFER_LIGHTING, 1, &mLightBuffer);
    }

    {
        //PROFILE_SCOPE(RenderObjects);
        // Draw the objects
        for (RenderObj* pObj : mRenderObj)
            pObj->Draw();
    }

    //mGraphic.BeginAlpha();
    //{
    //    //PROFILE_SCOPE(RenderParticles);
    //    // Draw the Particles
    //    ParticleEmitter::RenderAll();
    //}

    {
        //PROFILE_SCOPE(EndFrame);
        // Done with this frame
        mGraphic.EndFrame(1, 0);
    }
}

void Game::OnKeyDown(uint32_t key)
{
	m_keyIsHeld[key] = true;
}

void Game::OnKeyUp(uint32_t key)
{
	m_keyIsHeld[key] = false;
}

bool Game::IsKeyHeld(uint32_t key) const
{
	const auto find = m_keyIsHeld.find(key);
	if (find != m_keyIsHeld.end())
		return find->second;
	return false;
}

Light::PointLightData* Game::AllocateLight()
{
    for (int i = 0; i < Light::numPointLight; i++)
    {
        if (!mLightData.pointLightArray[i].isEnabled)
        {
            mLightData.pointLightArray[i].isEnabled = true;
            return &(mLightData.pointLightArray[i]);
        }
    }
    return nullptr;

}

void Game::FreeLight(Light::PointLightData* pLight)
{
    pLight->isEnabled = false;
}

void Game::SetAmbientLight(const Vector3& color)
{
    mLightData.ambientLight = color;
}

const Vector3& Game::GetAmbientLight() const
{
    return mLightData.ambientLight;
}

bool Game::LoadLevel(const WCHAR* fileName)
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
		return false;
	}

	std::string str = doc["metadata"]["type"].GetString();
	int ver = doc["metadata"]["version"].GetInt();

	// Check the metadata
	if (!doc["metadata"].IsObject() ||
		str != "itplevel" ||
		ver != 2)
	{
		return false;
	}

    { // Read the camera data
        const rapidjson::Value& camObj = doc["camera"];
        if (camObj.IsObject())
        {
            Vector3 pos = Vector3::Zero;
            GetVectorFromJSON(camObj, "position", pos);
            Quaternion rot = Quaternion::Identity;
            GetQuaternionFromJSON(camObj, "rotation", rot);
            mCamera->mView = Matrix4::CreateFromQuaternion(rot) * Matrix4::CreateTranslation(pos);
            mCamera->mView.Invert();
        }
    }

    { // Read the lighting data
        const rapidjson::Value& lightObj = doc["lightingData"];
        if (lightObj.IsObject())
        {
            Vector3 ambient;
            GetVectorFromJSON(lightObj, "ambient", ambient);
            SetAmbientLight(ambient);
        }
    }

    {   // Load the RenderObjs
        const rapidjson::Value& renderObjects = doc["renderObjects"];
        if (renderObjects.IsArray())
        {
            for (rapidjson::SizeType i = 0; i < renderObjects.Size(); ++i)
            {
                const rapidjson::Value& obj = renderObjects[i];
                Vector3 pos;
                GetVectorFromJSON(obj, "position", pos);
                Quaternion rot;
                GetQuaternionFromJSON(obj, "rotation", rot);
                float scale;
                GetFloatFromJSON(obj, "scale", scale);
                std::wstring mesh;
                GetWStringFromJSON(obj, "mesh", mesh);
                Mesh* pMesh = mAssetManager.LoadMesh(mesh);
                RenderObj* pObj = nullptr;
                SkinnedObj* pSkin = nullptr;
                if ((nullptr != pMesh) && (pMesh->IsSkinned()))
                {
                    pSkin = new SkinnedObj(pMesh);
                    pObj = pSkin;
                }
                else
                {
                    pObj = new RenderObj(pMesh);
                }
                pObj->mObjectData.modelToWorld =
                    Matrix4::CreateScale(scale)
                    * Matrix4::CreateFromQuaternion(rot)
                    * Matrix4::CreateTranslation(pos);

                const rapidjson::Value& components = obj["components"];
                if (components.IsArray())
                {
                    for (rapidjson::SizeType j = 0; j < components.Size(); ++j)
                    {
                        Component* pComp = nullptr;
                        const rapidjson::Value& comp = components[j];
                        std::string type;
                        GetStringFromJSON(comp, "type", type);
                        if (type == "PointLight")
                        {
                            pComp = new PointLight(this, pObj);
                        }
                        else if (type == "Character")
                        {
                            pComp = new Character(this, pSkin);
                        }
                        else if (type == "Player")
                        {
                            pComp = new Player(this, pSkin);
                        }
                        else if (type == "FollowCam")
                        {
                            pComp = new FollowCam(this, pObj);
                        }
                        else if (type == "CollisionBox")
                        {
                            pComp = new CollisionComponent(&mPhysics, pObj);
                        }
                        else if (type == "Particle")
                        {
                            pComp = new ParticleEmitter(pObj);
                        }
                        if (nullptr != pComp)
                        {
                            pComp->LoadProperties(comp);
                            pObj->AddComponent(pComp);
                        }
                    }
                }

                mRenderObj.push_back(pObj);
            }
        }
    }

	return true;
}
#pragma once
#include "Animation.h"
#include "mesh.h"
#include "Shader.h"
#include "Skeleton.h"
#include "texture.h"
#include "Material.h"
#include "assetCache.h"

class Graphics;

class AssetManager
{
public:
    AssetManager();
    ~AssetManager();

    void Clear() const;

    Shader* GetShader(const std::wstring& shaderName) const { return mShaderCache->Get(shaderName); }
    void SetShader(const std::wstring& shaderName, Shader* pShader) const
    {
        pShader->SetName(shaderName);
	    mShaderCache->Cache(shaderName, pShader);
    }

    Texture* LoadTexture(const std::wstring& fileName) const { return mTextureCache->Load(fileName); }

    Material* LoadMaterial(const std::wstring& materialName) const { return mMaterialCache->Load(materialName); }

    Mesh* GetMesh(const std::wstring& meshName) const { return mMeshCache->Get(meshName); }
    void SetMesh(const std::wstring& meshName, Mesh* pMesh) const { mMeshCache->Cache(meshName, pMesh); }
    Mesh* LoadMesh(const std::wstring& fileName) const { return mMeshCache->Load(fileName); }

    Skeleton* LoadSkeleton(const std::wstring& fileName) const { return mSkeletonCache->Load(fileName); }
    Animation* LoadAnimation(const std::wstring& fileName) const { return mAnimCache->Load(fileName); }

private:
    AssetCache<Shader>* mShaderCache;
    AssetCache<Texture>* mTextureCache;
    AssetCache<Material>* mMaterialCache;
    AssetCache<Mesh>* mMeshCache;
    AssetCache<Skeleton>* mSkeletonCache;
    AssetCache<Animation>* mAnimCache;
};

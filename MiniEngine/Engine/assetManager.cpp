#include "stdafx.h"
#include "assetManager.h"

AssetManager::AssetManager()
{
	mShaderCache = new AssetCache<Shader>(this);
	mTextureCache = new AssetCache<Texture>(this);
	mMaterialCache = new AssetCache<Material>(this);
	mMeshCache = new AssetCache<Mesh>(this);
	mSkeletonCache = new AssetCache<Skeleton>(this);
	mAnimCache = new AssetCache<Animation>(this);
}

AssetManager::~AssetManager()
{
	delete mShaderCache;
	delete mTextureCache;
	delete mMaterialCache;
	delete mMeshCache;
	delete mSkeletonCache;
	delete mAnimCache;
}
void AssetManager::Clear() const
{
    mShaderCache->Clear();
    mTextureCache->Clear();
    mMeshCache->Clear();
    mSkeletonCache->Clear();
    mAnimCache->Clear();
	mMaterialCache->Clear();
}
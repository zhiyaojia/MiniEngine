#pragma once

#include "engineMath.h"
#include "Graphics.h"

class AssetManager;
class Shader;
class Texture;
class VertexBuffer;

class Mesh
{
public:
	Mesh(AssetManager* pAssetManager, const VertexBuffer* pVertexBuffer, const Shader* pShader);
	~Mesh();

	void Draw() const;
	void SetTexture(int slot, const Texture* texture);

	bool Load(const WCHAR* fileName);
    bool IsSkinned() const { return mIsSkin; }
	static Mesh* StaticLoad(const WCHAR* fileName, AssetManager* pAssetManager);

protected:
    AssetManager* mAssetManager;
    const Shader* mShader;
    const VertexBuffer* mVertexBuffer;
    const Texture* mTexture[Graphics::TEXTURE_SLOT_TOTAL];
    bool mIsSkin;
};
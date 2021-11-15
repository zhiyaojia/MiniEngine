#pragma once
#include "Graphics.h"
#include "Material.h"

class AssetManager;
class Shader;
class Texture;
class VertexBuffer;

class Mesh
{
public:
	Mesh(const VertexBuffer* vertexBuffer, Material* material);
	~Mesh();

	void Draw() const;

	bool Load(const WCHAR* fileName, AssetManager* pAssetManager);
    bool IsSkinned() const { return mIsSkin; }
	static Mesh* StaticLoad(const WCHAR* fileName, AssetManager* pAssetManager);

protected:
	Material* mMaterial;
	const VertexBuffer* mVertexBuffer;
    bool mIsSkin;
};
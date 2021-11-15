#include "stdafx.h"
#include "RenderCube.h"
#include "assetManager.h"
#include "mesh.h"
#include "VertexBuffer.h"
#include "VertexFormats.h"

static VertexFormat::VertexPosNormalColorUV cubeVertex[] =
{
	{ Vector3(-0.5f,  0.5f, -0.5f),	Vector3(0.0f,  0.0f, -1.0f), Graphics::Color4(1.0f, 0.0f, 0.0f, 1.0f),   Vector2(0.0f, 0.0f) },
	{ Vector3(0.5f,  0.5f, -0.5f),	Vector3(0.0f,  0.0f, -1.0f), Graphics::Color4(1.0f, 0.0f, 0.0f, 1.0f),   Vector2(1.0f, 0.0f) },
	{ Vector3(0.5f, -0.5f, -0.5f),	Vector3(0.0f,  0.0f, -1.0f), Graphics::Color4(1.0f, 0.0f, 0.0f, 1.0f),   Vector2(1.0f, 1.0f) },
	{ Vector3(-0.5f, -0.5f, -0.5f),	Vector3(0.0f,  0.0f, -1.0f), Graphics::Color4(1.0f, 0.0f, 0.0f, 1.0f),   Vector2(0.0f, 1.0f) },

	{ Vector3(0.5f,  0.5f, -0.5f),	Vector3(1.0f,  0.0f,  0.0f), Graphics::Color4(0.0f, 1.0f, 0.0f, 1.0f),   Vector2(0.0f, 0.0f) },
	{ Vector3(0.5f,  0.5f,  0.5f),	Vector3(1.0f,  0.0f,  0.0f), Graphics::Color4(0.0f, 1.0f, 0.0f, 1.0f),   Vector2(1.0f, 0.0f) },
	{ Vector3(0.5f, -0.5f,  0.5f),	Vector3(1.0f,  0.0f,  0.0f), Graphics::Color4(0.0f, 1.0f, 0.0f, 1.0f),   Vector2(1.0f, 1.0f) },
	{ Vector3(0.5f, -0.5f, -0.5f),	Vector3(1.0f,  0.0f,  0.0f), Graphics::Color4(0.0f, 1.0f, 0.0f, 1.0f),   Vector2(0.0f, 1.0f) },

	{ Vector3(-0.5f, -0.5f,  0.5f),	Vector3(0.0f,  0.0f,  1.0f), Graphics::Color4(0.0f, 0.0f, 1.0f, 1.0f),   Vector2(0.0f, 0.0f) },
	{ Vector3(0.5f, -0.5f,  0.5f),	Vector3(0.0f,  0.0f,  1.0f), Graphics::Color4(0.0f, 0.0f, 1.0f, 1.0f),   Vector2(1.0f, 0.0f) },
	{ Vector3(0.5f,  0.5f,  0.5f),	Vector3(0.0f,  0.0f,  1.0f), Graphics::Color4(0.0f, 0.0f, 1.0f, 1.0f),   Vector2(1.0f, 1.0f) },
	{ Vector3(-0.5f,  0.5f,  0.5f),	Vector3(0.0f,  0.0f,  1.0f), Graphics::Color4(0.0f, 0.0f, 1.0f, 1.0f),   Vector2(0.0f, 1.0f) },

	{ Vector3(-0.5f, -0.5f, -0.5f),	Vector3(-1.0f,  0.0f,  0.0f), Graphics::Color4(1.0f, 1.0f, 0.0f, 1.0f),   Vector2(0.0f, 0.0f) },
	{ Vector3(-0.5f, -0.5f,  0.5f),	Vector3(-1.0f,  0.0f,  0.0f), Graphics::Color4(1.0f, 1.0f, 0.0f, 1.0f),   Vector2(1.0f, 0.0f) },
	{ Vector3(-0.5f,  0.5f,  0.5f),	Vector3(-1.0f,  0.0f,  0.0f), Graphics::Color4(1.0f, 1.0f, 0.0f, 1.0f),   Vector2(1.0f, 1.0f) },
	{ Vector3(-0.5f,  0.5f, -0.5f),	Vector3(-1.0f,  0.0f,  0.0f), Graphics::Color4(1.0f, 1.0f, 0.0f, 1.0f),   Vector2(0.0f, 1.0f) },

	{ Vector3(-0.5f, -0.5f, -0.5f),	Vector3(0.0f, -1.0f,  0.0f), Graphics::Color4(0.0f, 1.0f, 1.0f, 1.0f),   Vector2(0.0f, 0.0f) },
	{ Vector3(0.5f, -0.5f, -0.5f),	Vector3(0.0f, -1.0f,  0.0f), Graphics::Color4(0.0f, 1.0f, 1.0f, 1.0f),   Vector2(1.0f, 0.0f) },
	{ Vector3(0.5f, -0.5f,  0.5f),	Vector3(0.0f, -1.0f,  0.0f), Graphics::Color4(0.0f, 1.0f, 1.0f, 1.0f),   Vector2(1.0f, 1.0f) },
	{ Vector3(-0.5f, -0.5f,  0.5f),	Vector3(0.0f, -1.0f,  0.0f), Graphics::Color4(0.0f, 1.0f, 1.0f, 1.0f),   Vector2(0.0f, 1.0f) },

	{ Vector3(-0.5f,  0.5f,  0.5f),	Vector3(0.0f,  1.0f,  0.0f), Graphics::Color4(1.0f, 0.0f, 1.0f, 1.0f),   Vector2(0.0f, 0.0f) },
	{ Vector3(0.5f,  0.5f,  0.5f),	Vector3(0.0f,  1.0f,  0.0f), Graphics::Color4(1.0f, 0.0f, 1.0f, 1.0f),   Vector2(1.0f, 0.0f) },
	{ Vector3(0.5f,  0.5f, -0.5f),	Vector3(0.0f,  1.0f,  0.0f), Graphics::Color4(1.0f, 0.0f, 1.0f, 1.0f),   Vector2(1.0f, 1.0f) },
	{ Vector3(-0.5f,  0.5f, -0.5f),	Vector3(0.0f,  1.0f,  0.0f), Graphics::Color4(1.0f, 0.0f, 1.0f, 1.0f),   Vector2(0.0f, 1.0f) }
};

static uint16_t cubeIndex[] =
{
    2, 1, 0,
    3, 2, 0,

    6, 5, 4,
    7, 6, 4,

    10, 9, 8,
    11, 10, 8,

    14, 13, 12,
    15, 14, 12,

    18, 17, 16,
    19, 18, 16,

    22, 21, 20,
    23, 22, 20,
};

RenderCube::RenderCube(Material* material)
    : RenderObj(nullptr)
{
    mMesh = new Mesh
	(
        new VertexBuffer
        (
            cubeVertex, ARRAY_SIZE(cubeVertex), sizeof(VertexFormat::VertexPosNormalColorUV),
            cubeIndex, ARRAY_SIZE(cubeIndex), sizeof(uint16_t)
        ),
        material
    );
}

RenderCube::~RenderCube()
{
    delete mMesh;
}

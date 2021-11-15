#pragma once
#include "engineMath.h"
#include "Graphics.h"

namespace VertexFormat
{
	struct VertexPosColor
	{
		Vector3 pos;
		Graphics::Color4 color;
	};

	struct VertexPosColorUV
	{
		Vector3 pos;
		Graphics::Color4 color;
		Vector2 uv;
	};

	struct VertexPosUV
	{
		Vector3 pos;
		Vector2 uv;
	};

	struct VertexPosNormalColorUV
	{
		Vector3 pos;
		Vector3 norm;
		Graphics::Color4 color;
		Vector2 uv;
	};

	struct VertexPosNormalUV
	{
		Vector3 pos;
		Vector3 norm;
		Vector2 uv;
	};

	struct VertexPosNormSkinUV
	{
		Vector3 pos;
		Vector3 norm;
		uint8_t boneIndex[4];
		uint8_t boneWeight[4];
		Vector2 uv;
	};
}

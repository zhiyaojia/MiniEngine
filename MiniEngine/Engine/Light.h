#pragma once
#include "engineMath.h"

namespace Light
{
	constexpr int numPointLight = 8;

	struct PointLightData
	{
		PointLightData()
		{
			lightColor = Vector3::Zero;
			padding1 = 0.0f;
			position = Vector3::Zero;
			innerRadius = 0.0f;
			outerRadius = 0.0f;
			isEnabled = false;
			padding2 = 0.0f;
			padding3 = 0.0f;
		}
		Vector3 lightColor;
		float padding1;
		Vector3 position;
		float innerRadius;
		float outerRadius;
		bool isEnabled;
		float padding2;
		float padding3;
	};

	struct LightingConstant
	{
		LightingConstant() : ambientLight(Vector3::One), padding(0.0f) {}
		Vector3 ambientLight;
		float padding;
		PointLightData pointLightArray[numPointLight];
	};
}

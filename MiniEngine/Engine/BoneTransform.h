#pragma once
#include "engineMath.h"

class BoneTransform
{
public:
    BoneTransform(): mRotation(Quaternion::Identity), mTranslation(Vector3::Zero) {}

    Matrix4 ToMatrix() const
    {
	    return Matrix4::CreateFromQuaternion(mRotation) * Matrix4::CreateTranslation(mTranslation);
    }

    static BoneTransform Interpolate(const BoneTransform& a, const BoneTransform& b, float f);

    Quaternion mRotation;
    Vector3 mTranslation;
};
#include "stdafx.h"
#include "BoneTransform.h"

BoneTransform BoneTransform::Interpolate(const BoneTransform& a, const BoneTransform& b, float f)
{
    BoneTransform lerpTransform;
    lerpTransform.mRotation = Slerp(a.mRotation, b.mRotation, f);
    lerpTransform.mTranslation = Lerp(a.mTranslation, b.mTranslation, f);
    return lerpTransform;
}

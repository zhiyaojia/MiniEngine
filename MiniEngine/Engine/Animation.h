#pragma once
#include "BoneTransform.h"

class AssetManager;
class Skeleton;

class Animation
{
public:
    Animation();
    static Animation* StaticLoad(const WCHAR* fileName, AssetManager* pAssetManager);
    bool Load(const WCHAR* fileName);
    void GetGlobalPoseAtTime(std::vector<Matrix4>& outPoses, const Skeleton *inSkeleton, float inTime) const;

    uint32_t GetNumBones() const { return mBoneNum; }
    uint32_t GetNumFrames() const { return mFrameNum; }
    float GetLength() const { return mLength; }

private:
    uint32_t mBoneNum;
    uint32_t mFrameNum;
    float mLength;
    std::vector<std::vector<BoneTransform>> mTracks;
};
#pragma once
#include "BoneTransform.h"

class AssetManager;

class Skeleton
{
public:
    struct Bone
    {
        Bone(): mLocalTransform(BoneTransform()), mName(""), mParent(0) {}
        BoneTransform mLocalTransform;
        std::string mName;
        int mParent;
    };

    static size_t MAX_SKELETON_BONES;
    Skeleton();
    static Skeleton* StaticLoad(const WCHAR* fileName, AssetManager* pAssetManager);
    bool Load(const WCHAR* fileName);

    size_t GetNumBones() const { return mBones.size(); }
    const Bone& GetBone(size_t idx) const { return mBones[idx]; }
    const std::vector<Bone>& GetBones() const { return mBones; }
    const std::vector<Matrix4>& GetGlobalInvBindPoses() const { return mGlobalInverseBindPoses; }
private:
    void ComputeGlobalInvBindPose();

    std::vector<Bone> mBones;
    std::vector<Matrix4> mGlobalInverseBindPoses;
};
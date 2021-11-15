#include "stdafx.h"
#include "Skeleton.h"

#include "rapidjson\include\rapidjson\rapidjson.h"
#include "rapidjson\include\rapidjson\document.h"
#include <fstream>
#include <sstream>

size_t Skeleton::MAX_SKELETON_BONES = 80;

Skeleton::Skeleton()
{
}

void Skeleton::ComputeGlobalInvBindPose()
{
    mGlobalInverseBindPoses.resize(mBones.size());
    for (int i = 0; i < mBones.size(); ++i)
    {
        const Bone& bone = mBones[i];
        Matrix4 mat = bone.mLocalTransform.ToMatrix();
        if (bone.mParent >= 0)
        {
            mGlobalInverseBindPoses[i] = mat * mGlobalInverseBindPoses[bone.mParent];
        }
    }
    for (int i = 0; i < mBones.size(); ++i)
    {
        mGlobalInverseBindPoses[i].Invert();
    }
}

Skeleton* Skeleton::StaticLoad(const WCHAR* fileName, AssetManager* pAssetManager)
{
    Skeleton *pSkeleton = new Skeleton();
    if (false == pSkeleton->Load(fileName))
    {
        delete pSkeleton;
        return nullptr;
    }
    return pSkeleton;
}

bool Skeleton::Load(const WCHAR* fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        return false;
    }

    std::stringstream fileStream;
    fileStream << file.rdbuf();
    std::string contents = fileStream.str();
    rapidjson::StringStream jsonStr(contents.c_str());
    rapidjson::Document doc;
    doc.ParseStream(jsonStr);

    if (!doc.IsObject())
    {
        return false;
    }

    std::string str = doc["metadata"]["type"].GetString();
    int ver = doc["metadata"]["version"].GetInt();

    // Check the metadata
    if (!doc["metadata"].IsObject() ||
        str != "itpskel" ||
        ver != 1)
    {
        return false;
    }

    const rapidjson::Value& boneCount = doc["bonecount"];
    if (!boneCount.IsUint())
    {
        return false;
    }

    size_t count = boneCount.GetUint();

    DbgAssert(count <= Skeleton::MAX_SKELETON_BONES, "Skeleton exceeds maximum allowed bones.");

    mBones.reserve(count);

    const rapidjson::Value& bones = doc["bones"];
    if (!bones.IsArray())
    {
        return false;
    }

    if (bones.Size() != count)
    {
        return false;
    }

    Bone temp;

    for (rapidjson::SizeType i = 0; i < count; i++)
    {
        if (!bones[i].IsObject())
        {
            return false;
        }

        const rapidjson::Value& name = bones[i]["name"];
        temp.mName = name.GetString();

        const rapidjson::Value& parent = bones[i]["parent"];
        temp.mParent = parent.GetInt();

        const rapidjson::Value& bindpose = bones[i]["bindpose"];
        if (!bindpose.IsObject())
        {
            return false;
        }

        const rapidjson::Value& rot = bindpose["rot"];
        const rapidjson::Value& trans = bindpose["trans"];

        if (!rot.IsArray() || !trans.IsArray())
        {
            return false;
        }

        temp.mLocalTransform.mRotation.x = static_cast<float>(rot[0].GetDouble());
        temp.mLocalTransform.mRotation.y = static_cast<float>(rot[1].GetDouble());
        temp.mLocalTransform.mRotation.z = static_cast<float>(rot[2].GetDouble());
        temp.mLocalTransform.mRotation.w = static_cast<float>(rot[3].GetDouble());

        temp.mLocalTransform.mTranslation.x = static_cast<float>(trans[0].GetDouble());
        temp.mLocalTransform.mTranslation.y = static_cast<float>(trans[1].GetDouble());
        temp.mLocalTransform.mTranslation.z = static_cast<float>(trans[2].GetDouble());

        mBones.push_back(temp);
    }

    // Now that we have the bones
    ComputeGlobalInvBindPose();

    return true;
}


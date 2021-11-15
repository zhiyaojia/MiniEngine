#pragma once
#include "RenderObj.h"

class AssetManager;
class Shader;
class Texture;

class RenderCube :
    public RenderObj
{
public:
    RenderCube(class Material* material);
    virtual ~RenderCube() override;
};


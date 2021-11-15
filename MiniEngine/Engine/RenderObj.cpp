#include "stdafx.h"
#include "RenderObj.h"
#include "Components\Component.h"
#include "Graphics.h"
#include "mesh.h"


RenderObj::RenderObj(const Mesh* pMesh): mMesh(pMesh)
{
    mGraphics = Graphics::Get();
    mObjectData.modelToWorld = Matrix4::CreateRotationZ(Math::ToRadians(45.0f));
    mObjectBuffer = mGraphics->CreateGraphicsBuffer(&mObjectData, sizeof(mObjectData), D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE, D3D11_USAGE_DYNAMIC); 
}

RenderObj::~RenderObj()
{
    mObjectBuffer->Release();
}

void RenderObj::Draw()
{
    if (mMesh)
    {
        mGraphics->UploadBuffer(mObjectBuffer, &mObjectData, sizeof(mObjectData));
        mGraphics->GetDeviceContext()->VSSetConstantBuffers(Graphics::CONSTANT_BUFFER_RENDEROBJ, 1, &mObjectBuffer);
        mMesh->Draw();
    }
}

void RenderObj::Update(float deltaTime)
{
    for (Component* pComp : mComponents)
    {
        pComp->Update(deltaTime);
    }
}

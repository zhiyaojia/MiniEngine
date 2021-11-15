#include "stdafx.h"
#include "Shader.h"
#include "Graphics.h"
#include <d3dcompiler.h>
#include "VertexFormats.h"
#include "assetManager.h"
#include "Components/ParticleEmitter.h"

#pragma comment (lib, "d3dcompiler.lib") 

Shader::Shader()
    : mShaderVS(nullptr)
    , mShaderPS(nullptr)
    , mInputLayout(nullptr)
{
    mGraphics = Graphics::Get();
}

Shader::~Shader()
{
    mShaderVS->Release();
    mShaderPS->Release();
    mInputLayout->Release();
}

bool Shader::LoadShader(const WCHAR* filename, const char* entryPoint, const char* model, ID3DBlob*& pBlobOut)
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;

    // Disable optimizations to further improve shader debugging
    dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    ID3DBlob* pErrorBlob = nullptr;
    hr = D3DCompileFromFile(filename, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, model,
        dwShaderFlags, 0, &pBlobOut, &pErrorBlob);
    if (FAILED(hr))
    {
        if (pErrorBlob)
        {
            static wchar_t szBuffer[4096];
            _snwprintf_s(szBuffer, 4096, _TRUNCATE,
                L"%hs",
                (char*)pErrorBlob->GetBufferPointer());
            OutputDebugString(szBuffer);
#ifdef _WINDOWS
            MessageBox(nullptr, szBuffer, L"Error", MB_OK);
#endif
            pErrorBlob->Release();
        }
        return false;
    }
    if (pErrorBlob)
    {
        pErrorBlob->Release();
    }

    return true;
}

bool Shader::Load(const WCHAR* fileName, const D3D11_INPUT_ELEMENT_DESC* layoutArray, int numLayoutElements)
{
    ID3DBlob* pBlobVS = nullptr;
    if (LoadShader(fileName, "VS", "vs_4_0", pBlobVS))
    {
        ID3DBlob* pBlobPS = nullptr;
        if (LoadShader(fileName, "PS", "ps_4_0", pBlobPS))
        {
            Graphics* pGraphics = Graphics::Get();
            HRESULT hr = pGraphics->GetDevice()->CreateVertexShader(pBlobVS->GetBufferPointer(), pBlobVS->GetBufferSize(), nullptr, &mShaderVS);
            DbgAssert(hr == S_OK, "Failed to create vertex shader");
            hr = pGraphics->GetDevice()->CreatePixelShader(pBlobPS->GetBufferPointer(), pBlobPS->GetBufferSize(), nullptr, &mShaderPS);
            DbgAssert(hr == S_OK, "Failed to create pixel shader");
            if (nullptr != mShaderVS && nullptr != mShaderPS)
            {
                hr = pGraphics->GetDevice()->CreateInputLayout(layoutArray, numLayoutElements, pBlobVS->GetBufferPointer(), pBlobVS->GetBufferSize(), &mInputLayout);
                DbgAssert(hr == S_OK, "Failed to create input layout");
                if (S_OK == hr)
                    return true;
            }
            return false;
        }
    }
    DbgAssert(false, "Failed to load shader");
    return false;
}

void Shader::SetActive() const
{
    mGraphics->GetDeviceContext()->VSSetShader(mShaderVS, nullptr, 0);
    mGraphics->GetDeviceContext()->PSSetShader(mShaderPS, nullptr, 0);
    mGraphics->GetDeviceContext()->IASetInputLayout(mInputLayout);
}

void Shader::LoadAllShader(AssetManager* assetManager)
{
    {
        assetManager->SetShader(L"Mesh", new Shader());
        D3D11_INPUT_ELEMENT_DESC meshLayout[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, offsetof(VertexFormat::VertexPosColor, pos),   D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(VertexFormat::VertexPosColor, color), D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };
        assetManager->GetShader(L"Mesh")->Load(L"Shaders/Mesh.hlsl", meshLayout, ARRAY_SIZE(meshLayout));
    }

    {   // load the BasicMesh shader
        assetManager->SetShader(L"BasicMesh", new Shader());
        D3D11_INPUT_ELEMENT_DESC basicMeshLayout[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, offsetof(VertexFormat::VertexPosNormalColorUV, pos),   D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, offsetof(VertexFormat::VertexPosNormalColorUV, norm),  D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(VertexFormat::VertexPosNormalColorUV, color), D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, offsetof(VertexFormat::VertexPosNormalColorUV, uv),    D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };
        assetManager->GetShader(L"BasicMesh")->Load(L"Shaders/BasicMesh.hlsl", basicMeshLayout, ARRAY_SIZE(basicMeshLayout));
    }

    {
        assetManager->SetShader(L"Phong", new Shader());
        D3D11_INPUT_ELEMENT_DESC phongLayout[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexFormat::VertexPosNormalUV, pos), D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexFormat::VertexPosNormalUV, norm), D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(VertexFormat::VertexPosNormalUV, uv), D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };
        assetManager->GetShader(L"Phong")->Load(L"Shaders/Phong.hlsl", phongLayout, ARRAY_SIZE(phongLayout));
    }

    {
        assetManager->SetShader(L"Unlit", new Shader());
        D3D11_INPUT_ELEMENT_DESC unlitLayout[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexFormat::VertexPosNormalUV, pos), D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexFormat::VertexPosNormalUV, norm), D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(VertexFormat::VertexPosNormalUV, uv), D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };
        assetManager->GetShader(L"Unlit")->Load(L"Shaders/Unlit.hlsl", unlitLayout, ARRAY_SIZE(unlitLayout));
    }

    {
        assetManager->SetShader(L"Skinned", new Shader());
        D3D11_INPUT_ELEMENT_DESC inputElem[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, offsetof(VertexFormat::VertexPosNormSkinUV, pos),         D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, offsetof(VertexFormat::VertexPosNormSkinUV, norm),        D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "BONE",     0, DXGI_FORMAT_R8G8B8A8_UINT,      0, offsetof(VertexFormat::VertexPosNormSkinUV, boneIndex),   D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "WEIGHT",   0, DXGI_FORMAT_R8G8B8A8_UNORM,     0, offsetof(VertexFormat::VertexPosNormSkinUV, boneWeight),  D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, offsetof(VertexFormat::VertexPosNormSkinUV, uv),          D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };
        assetManager->GetShader(L"Skinned")->Load(L"Shaders/Skinned.hlsl", inputElem, ARRAY_SIZE(inputElem));
    }

    {
        assetManager->SetShader(L"Particle", new Shader());
        D3D11_INPUT_ELEMENT_DESC inputElem[] =
        {
            { "POSITION",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexFormat::VertexPosUV, pos),                               D3D11_INPUT_PER_VERTEX_DATA,    0 },
            { "TEXCOORD",   0, DXGI_FORMAT_R32G32_FLOAT,    0, offsetof(VertexFormat::VertexPosUV, uv),                                D3D11_INPUT_PER_VERTEX_DATA,    0 },
            { "POSITION",   1, DXGI_FORMAT_R32G32B32_FLOAT, 1, offsetof(ParticleEmitter::PerParticleRenderData, pos),    D3D11_INPUT_PER_INSTANCE_DATA,  1 },
            { "SIZE",       0, DXGI_FORMAT_R32_FLOAT,       1, offsetof(ParticleEmitter::PerParticleRenderData, size),   D3D11_INPUT_PER_INSTANCE_DATA,  1 },
            { "ALPHA",      0, DXGI_FORMAT_R32_FLOAT,       1, offsetof(ParticleEmitter::PerParticleRenderData, alpha),  D3D11_INPUT_PER_INSTANCE_DATA,  1 }
        };
        assetManager->GetShader(L"Particle")->Load(L"Shaders/Particle.hlsl", inputElem, ARRAY_SIZE(inputElem));
    }
}
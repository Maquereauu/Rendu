#include "framework.h"


void GCShaderTexture::CompileShader(HLSLFile* customShaderFile) {
    if (!customShaderFile) {
        std::cerr << "Invalid shader file." << std::endl;
        return;
    }
    m_vsByteCode = CompileShaderBase(customShaderFile->fileName, nullptr, "VS", "vs_5_0");
    m_psByteCode = CompileShaderBase(customShaderFile->fileName, nullptr, "PS", "ps_5_0");
    m_InputLayout =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
    };
}
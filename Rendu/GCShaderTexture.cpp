#include "framework.h"

void GCShaderTexture::CompileShader(std::wstring hlsl) {
	m_vsByteCode = CompileShaderBase(L"Shaders\\" + hlsl + L".hlsl", nullptr, "VS", "vs_5_0");
	m_psByteCode = CompileShaderBase(L"Shaders\\" + hlsl + L".hlsl", nullptr, "PS", "ps_5_0");
	m_InputLayout =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};
}
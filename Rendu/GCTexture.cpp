#include "framework.h"


GCTexture::GCTexture()
{
	GCRender r;
	SrvHeapIndex = 0;
	m_textureBuffer = nullptr;
	m_uploadTexture = nullptr;
}

GCTexture::~GCTexture()
{
	delete m_textureBuffer;
	delete m_uploadTexture;
}


bool GCTexture::Initialize(std::string fileName, GCGraphics* pGraphics)
{
	m_haepDescSize = pGraphics->GetRender()->Getmd3dDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	m_CbvSrvUavDescriptorSize = pGraphics->GetRender()->Getmd3dDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// Texture resource
	std::string Name = "ahah";
	std::wstring wideFileName(fileName.begin(), fileName.end());

	// Create the final filename
	std::wstringstream ss;
	ss << L"Textures/" << wideFileName << L".dds";
	std::wstring Filename = ss.str();

	DirectX::CreateDDSTextureFromFile12(pGraphics->GetRender()->Getmd3dDevice(), pGraphics->GetRender()->GetCommandList(), Filename.c_str(), &m_resource, &m_uploadHeap);
	if (m_resource == nullptr || m_uploadHeap == nullptr)
		return false;

	// Heap
	CD3DX12_CPU_DESCRIPTOR_HANDLE hDescriptor(pGraphics->GetRender()->GetCbvSrvUavSrvDescriptorHeap()->GetCPUDescriptorHandleForHeapStart());
	hDescriptor.Offset(pGraphics->GetTextureId(), m_haepDescSize);

	// Desc texture
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = m_resource->GetDesc().Format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = m_resource->GetDesc().MipLevels;
	srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;
	pGraphics->GetRender()->Getmd3dDevice()->CreateShaderResourceView(m_resource, &srvDesc, hDescriptor);
	//getGPU pour les dessiner	
	// Manager

	m_HDescriptorGPU = CD3DX12_GPU_DESCRIPTOR_HANDLE(pGraphics->GetRender()->GetCbvSrvUavSrvDescriptorHeap()->GetGPUDescriptorHandleForHeapStart());
	m_HDescriptorGPU.Offset(pGraphics->GetTextureId(), m_haepDescSize);
	return true;
	
}

void GCTexture::Render() {



}
#pragma once

class GCTexture
{
public:
	GCTexture();
	~GCTexture();

	void Initialize(std::string fileName, GCGraphics* pGraphics);

	void Render();
public:
	CD3DX12_GPU_DESCRIPTOR_HANDLE m_HDescriptorGPU;
private:

	std::string m_namePath;
	// 
	int SrvHeapIndex;



	ID3D12Resource* m_textureBuffer;
	ID3D12Resource* m_uploadTexture;
	ID3D12Resource* m_resource = nullptr;
	ID3D12Resource* m_uploadHeap = nullptr;
	UINT m_haepDescSize;
	UINT m_CbvSrvUavDescriptorSize;

	CD3DX12_GPU_DESCRIPTOR_HANDLE m_textureAdress;
};
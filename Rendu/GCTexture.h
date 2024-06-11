#pragma once

class GCTexture
{
public:
	GCTexture();
	~GCTexture();

	bool Initialize(std::string fileName, GCGraphics* pGraphics);

	CD3DX12_GPU_DESCRIPTOR_HANDLE GetDescGPU() const { return m_HDescriptorGPU; }
private:
	CD3DX12_GPU_DESCRIPTOR_HANDLE m_HDescriptorGPU;
	ID3D12Resource* m_uploadTexture;
	ID3D12Resource* m_resource = nullptr;
	ID3D12Resource* m_uploadHeap = nullptr;
	UINT m_heapDescSize;
	UINT m_CbvSrvUavDescriptorSize;

};
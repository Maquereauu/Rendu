#pragma once

class GCTexture
{
public:
    GCTexture();
    ~GCTexture();

    bool Initialize(std::string fileName, GCGraphics* pGraphics);


    inline UINT GetCbvSrvUavDescriptorSize() const { return m_cbvSrvUavDescriptorSize; }
    inline ID3D12Resource* GetTextureBuffer() const { return m_pTextureBuffer; }
    inline ID3D12Resource* GetUploadTexture() const { return m_pUploadTexture; }
    inline CD3DX12_GPU_DESCRIPTOR_HANDLE GetTextureAddress() const { return m_textureAddress; }

private:
    UINT m_cbvSrvUavDescriptorSize;
    ID3D12Resource* m_pTextureBuffer;
    ID3D12Resource* m_pUploadTexture;
    CD3DX12_GPU_DESCRIPTOR_HANDLE m_textureAddress;
};
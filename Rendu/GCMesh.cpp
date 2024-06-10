#include "framework.h"
GCMesh::GCMesh() {
}

GCMesh::~GCMesh() {

}

void GCMesh::Initialize(GCRender* pRender) {
    m_pRender = pRender;
}

void GCMesh::UploadGeometryDataColor(GCGeometry* pGeometry) {
    m_boxGeo = new MeshGeometry();
    std::vector<GCVERTEX> vertices = {};
    for (int i = 0; i < pGeometry->pos.size(); i++) {
        vertices.push_back({ pGeometry->pos[i], pGeometry->color[i] });
    }
    const UINT vbByteSize = static_cast<UINT>(vertices.size() * sizeof(GCVERTEX) );
    const UINT ibByteSize = static_cast<UINT>(pGeometry->indices.size() * sizeof(std::uint16_t));

    //m_boxGeo = new MeshGeometry();
    m_boxGeo->Name = "boxGeo";

    D3DCreateBlob(vbByteSize, &m_boxGeo->VertexBufferCPU);

    CopyMemory(m_boxGeo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

    D3DCreateBlob(ibByteSize, &m_boxGeo->IndexBufferCPU);

    CopyMemory(m_boxGeo->IndexBufferCPU->GetBufferPointer(), pGeometry->indices.data(), ibByteSize);


    m_boxGeo->VertexBufferGPU = CreateDefaultBuffer(m_pRender->Getmd3dDevice(),
        m_pRender->GetCommandList(), vertices.data(), vbByteSize, m_boxGeo->VertexBufferUploader);
    m_boxGeo->IndexBufferGPU = CreateDefaultBuffer(m_pRender->Getmd3dDevice(),
        m_pRender->GetCommandList(), pGeometry->indices.data(), ibByteSize, m_boxGeo->IndexBufferUploader);

    m_boxGeo->VertexByteStride = sizeof(GCVERTEX);
    m_boxGeo->VertexBufferByteSize = vbByteSize;
    m_boxGeo->IndexFormat = DXGI_FORMAT_R16_UINT;
    m_boxGeo->IndexBufferByteSize = ibByteSize;

    // Initialize submesh
    SubmeshGeometry submesh;
    submesh.IndexCount = static_cast<UINT>(pGeometry->indices.size());
    submesh.StartIndexLocation = 0;
    submesh.BaseVertexLocation = 0;

    // Assign submesh to box geometry
    //pGeometry->submesh = submesh;   

    m_boxGeo->DrawArgs["mesh"] = submesh;

}

void GCMesh::UploadGeometryDataTexture(GCGeometry* pGeometry) {
    std::vector<GCVERTEXTEXTURE> vertices = {};
    for (int i = 0; i < pGeometry->texC.size(); i++) {
        vertices.push_back({ pGeometry->pos[i], pGeometry->texC[i] });
    }

    const UINT vbByteSize = static_cast<UINT>(vertices.size() * sizeof(GCVERTEXTEXTURE));
    const UINT ibByteSize = static_cast<UINT>(pGeometry->indices.size() * sizeof(std::uint16_t));

    m_boxGeo = new MeshGeometry();
    m_boxGeo->Name = "boxGeo";

    D3DCreateBlob(vbByteSize, &m_boxGeo->VertexBufferCPU);

    CopyMemory(m_boxGeo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

    D3DCreateBlob(ibByteSize, &m_boxGeo->IndexBufferCPU);

    CopyMemory(m_boxGeo->IndexBufferCPU->GetBufferPointer(), pGeometry->indices.data(), ibByteSize);


    m_boxGeo->VertexBufferGPU = CreateDefaultBuffer(m_pRender->Getmd3dDevice(),
        m_pRender->GetCommandList(), vertices.data(), vbByteSize, m_boxGeo->VertexBufferUploader);
    m_boxGeo->IndexBufferGPU = CreateDefaultBuffer(m_pRender->Getmd3dDevice(),
        m_pRender->GetCommandList(), pGeometry->indices.data(), ibByteSize, m_boxGeo->IndexBufferUploader);

    m_boxGeo->VertexByteStride = sizeof(GCVERTEXTEXTURE);
    m_boxGeo->VertexBufferByteSize = vbByteSize;
    m_boxGeo->IndexFormat = DXGI_FORMAT_R16_UINT;
    m_boxGeo->IndexBufferByteSize = ibByteSize;

    // Initialize submesh
    SubmeshGeometry submesh;
    submesh.IndexCount = static_cast<UINT>(pGeometry->indices.size());
    submesh.StartIndexLocation = 0;
    submesh.BaseVertexLocation = 0;

    // Assign submesh to box geometry
    //pGeometry->submesh = submesh;
    m_boxGeo->DrawArgs["mesh"] = submesh;
}

MeshGeometry* GCMesh::GetBoxGeometry()
{
    return m_boxGeo;
}

ID3D12Resource* GCMesh::CreateDefaultBuffer(
    ID3D12Device* device,
    ID3D12GraphicsCommandList* cmdList,
    const void* initData,
    UINT64 byteSize,
    ID3D12Resource* uploadBuffer)
{
    ID3D12Resource* defaultBuffer;

    // Create the actual default buffer resource.
    CD3DX12_HEAP_PROPERTIES heapProp(D3D12_HEAP_TYPE_DEFAULT);
    CD3DX12_RESOURCE_DESC resDesc(CD3DX12_RESOURCE_DESC::Buffer(byteSize));
    device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resDesc,
        D3D12_RESOURCE_STATE_COMMON,
        nullptr,
        IID_PPV_ARGS(&defaultBuffer));

    // In order to copy CPU memory data into our default buffer, we need to create
    // an intermediate upload heap.

    CD3DX12_HEAP_PROPERTIES heapPropUp(D3D12_HEAP_TYPE_UPLOAD);
    CD3DX12_RESOURCE_DESC resDesc2(CD3DX12_RESOURCE_DESC::Buffer(byteSize));
    device->CreateCommittedResource(
        &heapPropUp,
        D3D12_HEAP_FLAG_NONE,
        &resDesc2,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&uploadBuffer));


    // Describe the data we want to copy into the default buffer.
    D3D12_SUBRESOURCE_DATA subResourceData = {};
    subResourceData.pData = initData;
    subResourceData.RowPitch = byteSize;
    subResourceData.SlicePitch = subResourceData.RowPitch;

    // Schedule to copy the data to the default buffer resource.  At a high level, the helper function UpdateSubresources
    // will copy the CPU memory into the intermediate upload heap.  Then, using ID3D12CommandList::CopySubresourceRegion,
    // the intermediate upload heap data will be copied to mBuffer.
    CD3DX12_RESOURCE_BARRIER ResBarrier(CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer,
        D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST));
    cmdList->ResourceBarrier(1, &ResBarrier);
    UpdateSubresources<1>(cmdList, defaultBuffer, uploadBuffer, 0, 0, 1, &subResourceData);
    CD3DX12_RESOURCE_BARRIER ResBarrier2(CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer,
        D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ));
    cmdList->ResourceBarrier(1, &ResBarrier2);

    // Note: uploadBuffer has to be kept alive after the above function calls because
    // the command list has not been executed yet that performs the actual copy.
    // The caller can Release the uploadBuffer after it knows the copy has been executed.


    return defaultBuffer;
}
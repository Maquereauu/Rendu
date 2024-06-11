#include "framework.h"

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


//// CLASS
GCMesh::GCMesh() {
}

GCMesh::~GCMesh() {

}

void GCMesh::Initialize(GCRender* pRender) {
    m_pRender = pRender;
    //m_Buffer = new UploadBuffer<ObjectConstants>(m_pRender->Getmd3dDevice(), 1, true);

    m_pObjectCB = new UploadBuffer<ObjectCB>(m_pRender->Getmd3dDevice(), 1, true);
    m_pCameraCB = new UploadBuffer<CameraCB>(m_pRender->Getmd3dDevice(), 1, true);

}

template<typename VertexType>
void GCMesh::UploadGeometryData(GCGeometry* pGeometry) {
    std::vector<VertexType> vertices;

    vertices.resize(pGeometry->pos.size());

    if constexpr (std::is_same<VertexType, GCVERTEX>::value) {
        for (size_t i = 0; i < pGeometry->pos.size(); ++i) {
            vertices[i] = VertexType(pGeometry->pos[i], pGeometry->color[i]);
        }
    }
    else if constexpr (std::is_same<VertexType, GCVERTEXTEXTURE>::value) {
        for (size_t i = 0; i < pGeometry->pos.size(); ++i) {
            vertices[i] = VertexType(pGeometry->pos[i], pGeometry->texC[i]);
        }
    }
    
    

    const UINT vbByteSize = static_cast<UINT>(vertices.size() * sizeof(VertexType));
    const UINT ibByteSize = static_cast<UINT>(pGeometry->indices.size() * sizeof(std::uint16_t));

    m_pBufferGeometryData = new MeshGeometry();
    m_pBufferGeometryData->Name = "boxGeo";

    D3DCreateBlob(vbByteSize, &m_pBufferGeometryData->VertexBufferCPU);
    CopyMemory(m_pBufferGeometryData->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

    D3DCreateBlob(ibByteSize, &m_pBufferGeometryData->IndexBufferCPU);
    CopyMemory(m_pBufferGeometryData->IndexBufferCPU->GetBufferPointer(), pGeometry->indices.data(), ibByteSize);

    m_pBufferGeometryData->VertexBufferGPU = CreateDefaultBuffer(m_pRender->Getmd3dDevice(), m_pRender->GetCommandList(), vertices.data(), vbByteSize, m_pBufferGeometryData->VertexBufferUploader);
    m_pBufferGeometryData->IndexBufferGPU = CreateDefaultBuffer(m_pRender->Getmd3dDevice(), m_pRender->GetCommandList(), pGeometry->indices.data(), ibByteSize, m_pBufferGeometryData->IndexBufferUploader);

    m_pBufferGeometryData->VertexByteStride = sizeof(VertexType);
    m_pBufferGeometryData->VertexBufferByteSize = vbByteSize;
    m_pBufferGeometryData->IndexFormat = DXGI_FORMAT_R16_UINT;
    m_pBufferGeometryData->IndexBufferByteSize = ibByteSize;

    // Initialize submesh
    SubmeshGeometry submesh;
    submesh.IndexCount = static_cast<UINT>(pGeometry->indices.size());
    submesh.StartIndexLocation = 0;
    submesh.BaseVertexLocation = 0;

    m_pBufferGeometryData->DrawArgs["mesh"] = submesh;
}


void GCMesh::UploadGeometryDataColor(GCGeometry* pGeometry) {
    UploadGeometryData<GCVERTEX>(pGeometry);
}
void GCMesh::UploadGeometryDataTexture(GCGeometry* pGeometry) {
    UploadGeometryData<GCVERTEXTEXTURE>(pGeometry);
}


//void GCMesh::UpdateBuffer(DirectX::XMMATRIX worldViewProj)
//{
//    ObjectConstants objConstants;
//    XMStoreFloat4x4(&objConstants.WorldViewProj, worldViewProj);
//    m_Buffer->CopyData(0, objConstants);
//}

void GCMesh::UpdateObjectBuffer(DirectX::XMMATRIX worldMatrix)
{
    // Transposer la matrice du monde
    worldMatrix = DirectX::XMMatrixTranspose(worldMatrix);

    // Constant buffer pour la matrice du monde
    ObjectCB objectCB;
    XMStoreFloat4x4(&objectCB.world, worldMatrix);
    m_pObjectCB->CopyData(0, objectCB);
}

void GCMesh::UpdateCameraBuffer(DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX projMatrix)
{
    // Transposer les matrices de vue et de projection
    viewMatrix = DirectX::XMMatrixTranspose(viewMatrix);
    projMatrix = DirectX::XMMatrixTranspose(projMatrix);

    // Constant buffer pour les matrices de vue-projection
    CameraCB cameraCB;
    XMStoreFloat4x4(&cameraCB.view, viewMatrix);
    XMStoreFloat4x4(&cameraCB.proj, projMatrix);
    m_pCameraCB->CopyData(0, cameraCB);
}

////


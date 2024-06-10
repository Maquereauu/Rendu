#include "framework.h"
GCMesh::GCMesh() {
}

GCMesh::~GCMesh() {

}

void GCMesh::Initialize(GCRender* pRender) {
    m_pRender = pRender;
    //CreateboxGeometry();
    //CreateBoxGeometryTexture();
    //CreateObjGeometryTexture();
    //CreateObjGeometryColor();
}

//void GCMesh::CreatePrimitiveGeometry(int id) {
//    switch (id) {
//    case PIEnum::BoxColor: {
//        CreateboxGeometry(id);
//        break;
//    }
//
//    case PIEnum::BoxTexture: {
//        CreateBoxGeometryTexture(id);
//        break;
//    }
//
//    case PIEnum::PlaneTexture: {
//        CreateBoxGeometryTexture(id);
//        break;
//    }
//    }
//}
//
//void GCMesh::CreateObjGeometry(std::wstring obj, bool isTextured)
//{
//    if (isTextured)
//    {
//        CreateObjGeometryTexture(obj);
//    }
//    else {
//        CreateObjGeometryColor(obj);
//    }
//}

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

    ThrowIfFailed(D3DCreateBlob(vbByteSize, &m_boxGeo->VertexBufferCPU));

    CopyMemory(m_boxGeo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

    ThrowIfFailed(D3DCreateBlob(ibByteSize, &m_boxGeo->IndexBufferCPU));

    CopyMemory(m_boxGeo->IndexBufferCPU->GetBufferPointer(), pGeometry->indices.data(), ibByteSize);


    m_boxGeo->VertexBufferGPU = d3dUtil::CreateDefaultBuffer(m_pRender->Getmd3dDevice(),
        m_pRender->GetCommandList(), vertices.data(), vbByteSize, m_boxGeo->VertexBufferUploader);
    m_boxGeo->IndexBufferGPU = d3dUtil::CreateDefaultBuffer(m_pRender->Getmd3dDevice(),
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

    ThrowIfFailed(D3DCreateBlob(vbByteSize, &m_boxGeo->VertexBufferCPU));

    CopyMemory(m_boxGeo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

    ThrowIfFailed(D3DCreateBlob(ibByteSize, &m_boxGeo->IndexBufferCPU));

    CopyMemory(m_boxGeo->IndexBufferCPU->GetBufferPointer(), pGeometry->indices.data(), ibByteSize);


    m_boxGeo->VertexBufferGPU = d3dUtil::CreateDefaultBuffer(m_pRender->Getmd3dDevice(),
        m_pRender->GetCommandList(), vertices.data(), vbByteSize, m_boxGeo->VertexBufferUploader);
    m_boxGeo->IndexBufferGPU = d3dUtil::CreateDefaultBuffer(m_pRender->Getmd3dDevice(),
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

/*
void GCMesh::CreateboxGeometry(int id)
{
    PrimitiveFactory* factory = new PrimitiveFactory();
    factory->Initialize(id, m_pRender);
    m_pGeometry = factory->BuildGeometryColor();

    UploadGeometryDataColor();

    m_pGeometry->boxGeo->DrawArgs["box"] = m_pGeometry->submesh;
}

void GCMesh::CreateBoxGeometryTexture(int id)
{
    PrimitiveFactory* factory = new PrimitiveFactory();
    factory->Initialize(id, m_pRender);

    m_pGeometry = factory->BuildGeometryTexture();
    UploadGeometryDataTexture();

    m_pGeometry->boxGeo->DrawArgs["box"] = m_pGeometry->submesh;


}
//
void GCMesh::CreateObjGeometryColor(std::wstring obj)
{
    ModelParserObj* objParser = new ModelParserObj();
    objParser->Initialize(m_pRender, obj);
    objParser->ParseObj();
    m_pGeometry = objParser->BuildObjColor();

    UploadGeometryDataColor();

    m_pGeometry->boxGeo->DrawArgs["box"] = m_pGeometry->submesh;

}

void GCMesh::CreateObjGeometryTexture(std::wstring obj)
{
    ModelParserObj* objParser = new ModelParserObj();
    objParser->Initialize(m_pRender, obj);
    objParser->ParseObj();
    m_pGeometry = objParser->BuildObjTexture();

    UploadGeometryDataTexture();

    m_pGeometry->boxGeo->DrawArgs["box"] = m_pGeometry->submesh;
}*/



MeshGeometry* GCMesh::GetBoxGeometry()
{
    return m_boxGeo;
}

//GCGEOMETRYTEXTURE* GCMesh::GetGeometryTexture()
//{
//	return m_boxGeometryTexture;
//}




//void GCMesh::Render() {
//
//
//
//
//    //m_pRender->GetCommandList()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//    //D3D12_VERTEX_BUFFER_VIEW vertexBufferView = m_boxGeometry->boxGeo->VertexBufferView();
//    //m_pRender->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);
//    //D3D12_INDEX_BUFFER_VIEW indexBufferView = m_boxGeometry->boxGeo->IndexBufferView();
//    //m_pRender->GetCommandList()->IASetIndexBuffer(&indexBufferView);
//
//    //OutputDebugString(L"Set index buffer");
//
//    //DirectX::XMFLOAT3 pos1 = { 0.f, 0.f, 0.f };
//    //DirectX::XMVECTOR pos = DirectX::XMVectorSet(10, 10, 10, 1.0f);
//    //DirectX::XMVECTOR target = DirectX::XMVectorZero();
//    //DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
//
//    //DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(pos, target, up);
//    //DirectX::XMFLOAT4X4 MId = MathHelper::Identity4x4();
//    //DirectX::XMMATRIX world = DirectX::XMLoadFloat4x4(&MId);
//    //DirectX::XMMATRIX proj = DirectX::XMLoadFloat4x4(&mProj);
//    //DirectX::XMMATRIX worldViewProj = world * view * proj;
//
//    //m_Buffer = std::make_unique<UploadBuffer<ObjectConstants>>(m_pRender->Getmd3dDevice(), 1, true);
//    //ObjectConstants objConstants;
//    //XMStoreFloat4x4(&objConstants.WorldViewProj, XMMatrixTranspose(worldViewProj));
//    //m_Buffer->CopyData(0, objConstants);
//    //m_pRender->GetCommandList()->SetGraphicsRootConstantBufferView(0, m_Buffer->Resource()->GetGPUVirtualAddress());
//
//    //m_pRender->GetCommandList()->DrawIndexedInstanced(m_boxGeometry->boxGeo->DrawArgs["box"].IndexCount, 1, 0, 0, 0);
//
//
//
//}
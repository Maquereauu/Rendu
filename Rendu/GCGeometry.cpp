#include "framework.h"
GCGeometry::GCGeometry() {
}

GCGeometry::~GCGeometry() {

}

void GCGeometry::Initialize(GCRender* pRender) {
    m_pRender = pRender;
    //CreateBoxGeometryColor();
    //CreateBoxGeometryTexture();
    //CreateObjGeometryTexture();
    //CreateObjGeometryColor();
}

void GCGeometry::CreatePrimitiveGeometry(int id) {
    switch (id) {
    case PIEnum::BoxColor: {
        CreateBoxGeometryColor(id);
        break;
    }

    case PIEnum::BoxTexture: {
        CreateBoxGeometryTexture(id);
        break;
    }

    case PIEnum::PlaneTexture: {
        CreateBoxGeometryTexture(id);
        break;
    }
    }
}

void GCGeometry::CreateObjGeometry(std::wstring obj, bool isTextured)
{
    if (isTextured)
    {
        CreateObjGeometryTexture(obj);
    }
    else {
        CreateObjGeometryColor(obj);
    }
}

void GCGeometry::UploadGeometryDataColor() {
    GCGeo* boxGeometryColor = new GCGeo();

    const std::vector<DirectX::XMFLOAT3, DirectX::XMFLOAT4> vertices = std::vector<boxGeometryColor->pos, boxGeometryColor->color>;

    const UINT vbByteSize = static_cast<UINT>(vertices.size() * sizeof(GCVERTEX));
    const UINT ibByteSize = static_cast<UINT>(m_pGeometry->indices.size() * sizeof(std::uint16_t));

    boxGeometryColor->boxGeo = std::make_unique<MeshGeometry>();
    boxGeometryColor->boxGeo->Name = "boxGeo";

    ThrowIfFailed(D3DCreateBlob(vbByteSize, &boxGeometryColor->boxGeo->VertexBufferCPU));

    CopyMemory(boxGeometryColor->boxGeo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

    ThrowIfFailed(D3DCreateBlob(ibByteSize, &boxGeometryColor->boxGeo->IndexBufferCPU));

    CopyMemory(boxGeometryColor->boxGeo->IndexBufferCPU->GetBufferPointer(), m_pGeometry->indices.data(), ibByteSize);


    boxGeometryColor->boxGeo->VertexBufferGPU = d3dUtil::CreateDefaultBuffer(m_pRender->Getmd3dDevice(),
        m_pRender->GetCommandList(), vertices.data(), vbByteSize, boxGeometryColor->boxGeo->VertexBufferUploader);
    boxGeometryColor->boxGeo->IndexBufferGPU = d3dUtil::CreateDefaultBuffer(m_pRender->Getmd3dDevice(),
        m_pRender->GetCommandList(), m_pGeometry->indices.data(), ibByteSize, boxGeometryColor->boxGeo->IndexBufferUploader);

    boxGeometryColor->boxGeo->VertexByteStride = sizeof(GCVERTEX);
    boxGeometryColor->boxGeo->VertexBufferByteSize = vbByteSize;
    boxGeometryColor->boxGeo->IndexFormat = DXGI_FORMAT_R16_UINT;
    boxGeometryColor->boxGeo->IndexBufferByteSize = ibByteSize;

    // Initialize submesh
    SubmeshGeometry submesh;
    submesh.IndexCount = static_cast<UINT>(m_pGeometry->indices.size());
    submesh.StartIndexLocation = 0;
    submesh.BaseVertexLocation = 0;

    // Assign submesh to box geometry
    boxGeometryColor->submesh = submesh;

}


void GCGeometry::UploadGeometryDataTexture() {
    GCGeometryTexture* boxGeometryColor = dynamic_cast<GCGeometryTexture*>(m_pGeometry);
    if (!boxGeometryColor) {
        return;
    }

    const auto& vertices = boxGeometryColor->vertices;

    const UINT vbByteSize = static_cast<UINT>(vertices.size() * sizeof(GCVERTEXTEXTURE));
    const UINT ibByteSize = static_cast<UINT>(m_pGeometry->indices.size() * sizeof(std::uint16_t));

    boxGeometryColor->boxGeo = std::make_unique<MeshGeometry>();
    boxGeometryColor->boxGeo->Name = "boxGeo";

    ThrowIfFailed(D3DCreateBlob(vbByteSize, &boxGeometryColor->boxGeo->VertexBufferCPU));

    CopyMemory(boxGeometryColor->boxGeo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

    ThrowIfFailed(D3DCreateBlob(ibByteSize, &boxGeometryColor->boxGeo->IndexBufferCPU));

    CopyMemory(boxGeometryColor->boxGeo->IndexBufferCPU->GetBufferPointer(), m_pGeometry->indices.data(), ibByteSize);


    boxGeometryColor->boxGeo->VertexBufferGPU = d3dUtil::CreateDefaultBuffer(m_pRender->Getmd3dDevice(),
        m_pRender->GetCommandList(), vertices.data(), vbByteSize, boxGeometryColor->boxGeo->VertexBufferUploader);
    boxGeometryColor->boxGeo->IndexBufferGPU = d3dUtil::CreateDefaultBuffer(m_pRender->Getmd3dDevice(),
        m_pRender->GetCommandList(), m_pGeometry->indices.data(), ibByteSize, boxGeometryColor->boxGeo->IndexBufferUploader);

    boxGeometryColor->boxGeo->VertexByteStride = sizeof(GCVERTEXTEXTURE);
    boxGeometryColor->boxGeo->VertexBufferByteSize = vbByteSize;
    boxGeometryColor->boxGeo->IndexFormat = DXGI_FORMAT_R16_UINT;
    boxGeometryColor->boxGeo->IndexBufferByteSize = ibByteSize;

    // Initialize submesh
    SubmeshGeometry submesh;
    submesh.IndexCount = static_cast<UINT>(m_pGeometry->indices.size());
    submesh.StartIndexLocation = 0;
    submesh.BaseVertexLocation = 0;

    // Assign submesh to box geometry
    boxGeometryColor->submesh = submesh;
}


void GCGeometry::CreateBoxGeometryColor(int id)
{
    PrimitiveFactory* factory = new PrimitiveFactory();
    factory->Initialize(id, m_pRender);
    m_pGeometry = factory->BuildGeometryColor();

    UploadGeometryDataColor();

    m_pGeometry->boxGeo->DrawArgs["box"] = m_pGeometry->submesh;
}

void GCGeometry::CreateBoxGeometryTexture(int id)
{
    PrimitiveFactory* factory = new PrimitiveFactory();
    factory->Initialize(id, m_pRender);

    m_pGeometry = factory->BuildGeometryTexture();
    UploadGeometryDataTexture();

    m_pGeometry->boxGeo->DrawArgs["box"] = m_pGeometry->submesh;


}
//
void GCGeometry::CreateObjGeometryColor(std::wstring obj)
{
    ModelParserObj* objParser = new ModelParserObj();
    objParser->Initialize(m_pRender, obj);
    objParser->ParseObj();
    m_pGeometry = objParser->BuildObjColor();

    UploadGeometryDataColor();

    m_pGeometry->boxGeo->DrawArgs["box"] = m_pGeometry->submesh;

}

void GCGeometry::CreateObjGeometryTexture(std::wstring obj)
{
    ModelParserObj* objParser = new ModelParserObj();
    objParser->Initialize(m_pRender, obj);
    objParser->ParseObj();
    m_pGeometry = objParser->BuildObjTexture();

    UploadGeometryDataTexture();

    m_pGeometry->boxGeo->DrawArgs["box"] = m_pGeometry->submesh;
}



GCGeometry* GCGeometry::GetBoxGeometry()
{
    return m_pGeometry;
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
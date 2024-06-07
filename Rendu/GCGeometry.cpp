//#include "framework.h"
//GCGeometry::GCGeometry() {
//}
//
//GCGeometry::~GCGeometry() {
//
//}
//
//void GCGeometry::Initialize(GCRender* pRender) {
//    m_pRender = pRender;
//    //CreateboxGeometry();
//    //CreateBoxGeometryTexture();
//    //CreateObjGeometryTexture();
//    //CreateObjGeometryColor();
//}
//
//void GCGeometry::CreatePrimitiveGeometry(int id) {
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
//void GCGeometry::CreateObjGeometry(std::wstring obj, bool isTextured)
//{
//    if (isTextured)
//    {
//        CreateObjGeometryTexture(obj);
//    }
//    else {
//        CreateObjGeometryColor(obj);
//    }
//}
//
//void GCGeometry::UploadGeometryDataColor() {
//    GCGeo* boxGeometry = new GCGeo();
//    std::vector<GCVERTEX> vertices = {};
//    std::vector<GCVERTEXTEXTURE> verticesTex = {};
//    if (boxGeometry->texC.size() == 0)
//    {
//        for (int i = 0; i < boxGeometry->pos.size(); i++) {
//            vertices.push_back({ boxGeometry->pos[i], boxGeometry->color[i] });
//        }
//    }
//    else {
//        for (int i = 0; i < boxGeometry->pos.size(); i++) {
//            verticesTex.push_back({ boxGeometry->pos[i], boxGeometry->texC[i] });
//        }
//    }
//    //std::vector<GCVERTEX> vertices = {};
//    //for (int i = 0; i < boxGeometry->pos.size(); i++) {
//    //    vertices.push_back({ boxGeometry->pos[i], boxGeometry->color[i] });
//    //}
//
//    const UINT vbByteSize = static_cast<UINT>(boxGeometry->texC.size() == 0?vertices.size() * sizeof(GCVERTEX):verticesTex * sizeof(GCVERTEXTEXTURE));
//    const UINT ibByteSize = static_cast<UINT>(m_pGeometry->indices.size() * sizeof(std::uint16_t));
//
//    boxGeometry->boxGeo = std::make_unique<MeshGeometry>();
//    boxGeometry->boxGeo->Name = "boxGeo";
//
//    ThrowIfFailed(D3DCreateBlob(vbByteSize, &boxGeometry->boxGeo->VertexBufferCPU));
//
//    CopyMemory(boxGeometry->boxGeo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);
//
//    ThrowIfFailed(D3DCreateBlob(ibByteSize, &boxGeometry->boxGeo->IndexBufferCPU));
//
//    CopyMemory(boxGeometry->boxGeo->IndexBufferCPU->GetBufferPointer(), m_pGeometry->indices.data(), ibByteSize);
//
//
//    boxGeometry->boxGeo->VertexBufferGPU = d3dUtil::CreateDefaultBuffer(m_pRender->Getmd3dDevice(),
//        m_pRender->GetCommandList(), vertices.data(), vbByteSize, boxGeometry->boxGeo->VertexBufferUploader);
//    boxGeometry->boxGeo->IndexBufferGPU = d3dUtil::CreateDefaultBuffer(m_pRender->Getmd3dDevice(),
//        m_pRender->GetCommandList(), m_pGeometry->indices.data(), ibByteSize, boxGeometry->boxGeo->IndexBufferUploader);
//
//    boxGeometry->boxGeo->VertexByteStride = sizeof(GCVERTEX);
//    boxGeometry->boxGeo->VertexBufferByteSize = vbByteSize;
//    boxGeometry->boxGeo->IndexFormat = DXGI_FORMAT_R16_UINT;
//    boxGeometry->boxGeo->IndexBufferByteSize = ibByteSize;
//
//    // Initialize submesh
//    SubmeshGeometry submesh;
//    submesh.IndexCount = static_cast<UINT>(m_pGeometry->indices.size());
//    submesh.StartIndexLocation = 0;
//    submesh.BaseVertexLocation = 0;
//
//    // Assign submesh to box geometry
//    boxGeometry->submesh = submesh;
//
//}
//
//
//void GCGeometry::UploadGeometryDataTexture() {
//    GCGeo* boxGeometry = new GCGeo();
//    std::vector<GCVERTEXTEXTURE> vertices = {};
//    for (int i = 0; i < boxGeometry->pos.size(); i++) {
//        vertices.push_back({ boxGeometry->pos[i], boxGeometry->texC[i] });
//    }
//
//    const UINT vbByteSize = static_cast<UINT>(vertices.size() * sizeof(GCVERTEXTEXTURE));
//    const UINT ibByteSize = static_cast<UINT>(m_pGeometry->indices.size() * sizeof(std::uint16_t));
//
//    boxGeometry->boxGeo = std::make_unique<MeshGeometry>();
//    boxGeometry->boxGeo->Name = "boxGeo";
//
//    ThrowIfFailed(D3DCreateBlob(vbByteSize, &boxGeometry->boxGeo->VertexBufferCPU));
//
//    CopyMemory(boxGeometry->boxGeo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);
//
//    ThrowIfFailed(D3DCreateBlob(ibByteSize, &boxGeometry->boxGeo->IndexBufferCPU));
//
//    CopyMemory(boxGeometry->boxGeo->IndexBufferCPU->GetBufferPointer(), m_pGeometry->indices.data(), ibByteSize);
//
//
//    boxGeometry->boxGeo->VertexBufferGPU = d3dUtil::CreateDefaultBuffer(m_pRender->Getmd3dDevice(),
//        m_pRender->GetCommandList(), vertices.data(), vbByteSize, boxGeometry->boxGeo->VertexBufferUploader);
//    boxGeometry->boxGeo->IndexBufferGPU = d3dUtil::CreateDefaultBuffer(m_pRender->Getmd3dDevice(),
//        m_pRender->GetCommandList(), m_pGeometry->indices.data(), ibByteSize, boxGeometry->boxGeo->IndexBufferUploader);
//
//    boxGeometry->boxGeo->VertexByteStride = sizeof(GCVERTEXTEXTURE);
//    boxGeometry->boxGeo->VertexBufferByteSize = vbByteSize;
//    boxGeometry->boxGeo->IndexFormat = DXGI_FORMAT_R16_UINT;
//    boxGeometry->boxGeo->IndexBufferByteSize = ibByteSize;
//
//    // Initialize submesh
//    SubmeshGeometry submesh;
//    submesh.IndexCount = static_cast<UINT>(m_pGeometry->indices.size());
//    submesh.StartIndexLocation = 0;
//    submesh.BaseVertexLocation = 0;
//
//    // Assign submesh to box geometry
//    boxGeometry->submesh = submesh;
//}
//
//
//void GCGeometry::CreateboxGeometry(int id)
//{
//    PrimitiveFactory* factory = new PrimitiveFactory();
//    factory->Initialize(id, m_pRender);
//    m_pGeometry = factory->BuildGeometryColor();
//
//    UploadGeometryDataColor();
//
//    m_pGeometry->boxGeo->DrawArgs["box"] = m_pGeometry->submesh;
//}
//
//void GCGeometry::CreateBoxGeometryTexture(int id)
//{
//    PrimitiveFactory* factory = new PrimitiveFactory();
//    factory->Initialize(id, m_pRender);
//
//    m_pGeometry = factory->BuildGeometryTexture();
//    UploadGeometryDataTexture();
//
//    m_pGeometry->boxGeo->DrawArgs["box"] = m_pGeometry->submesh;
//
//
//}
////
//void GCGeometry::CreateObjGeometryColor(std::wstring obj)
//{
//    ModelParserObj* objParser = new ModelParserObj();
//    objParser->Initialize(m_pRender, obj);
//    objParser->ParseObj();
//    m_pGeometry = objParser->BuildObjColor();
//
//    UploadGeometryDataColor();
//
//    m_pGeometry->boxGeo->DrawArgs["box"] = m_pGeometry->submesh;
//
//}
//
//void GCGeometry::CreateObjGeometryTexture(std::wstring obj)
//{
//    ModelParserObj* objParser = new ModelParserObj();
//    objParser->Initialize(m_pRender, obj);
//    objParser->ParseObj();
//    m_pGeometry = objParser->BuildObjTexture();
//
//    UploadGeometryDataTexture();
//
//    m_pGeometry->boxGeo->DrawArgs["box"] = m_pGeometry->submesh;
//}
//
//
//
//GCGeometry* GCGeometry::GetBoxGeometry()
//{
//    return m_pGeometry;
//}
//
////GCGEOMETRYTEXTURE* GCMesh::GetGeometryTexture()
////{
////	return m_boxGeometryTexture;
////}
//
//
//
//
////void GCMesh::Render() {
////
////
////
////
////    //m_pRender->GetCommandList()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
////    //D3D12_VERTEX_BUFFER_VIEW vertexBufferView = m_boxGeometry->boxGeo->VertexBufferView();
////    //m_pRender->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);
////    //D3D12_INDEX_BUFFER_VIEW indexBufferView = m_boxGeometry->boxGeo->IndexBufferView();
////    //m_pRender->GetCommandList()->IASetIndexBuffer(&indexBufferView);
////
////    //OutputDebugString(L"Set index buffer");
////
////    //DirectX::XMFLOAT3 pos1 = { 0.f, 0.f, 0.f };
////    //DirectX::XMVECTOR pos = DirectX::XMVectorSet(10, 10, 10, 1.0f);
////    //DirectX::XMVECTOR target = DirectX::XMVectorZero();
////    //DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
////
////    //DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(pos, target, up);
////    //DirectX::XMFLOAT4X4 MId = MathHelper::Identity4x4();
////    //DirectX::XMMATRIX world = DirectX::XMLoadFloat4x4(&MId);
////    //DirectX::XMMATRIX proj = DirectX::XMLoadFloat4x4(&mProj);
////    //DirectX::XMMATRIX worldViewProj = world * view * proj;
////
////    //m_Buffer = std::make_unique<UploadBuffer<ObjectConstants>>(m_pRender->Getmd3dDevice(), 1, true);
////    //ObjectConstants objConstants;
////    //XMStoreFloat4x4(&objConstants.WorldViewProj, XMMatrixTranspose(worldViewProj));
////    //m_Buffer->CopyData(0, objConstants);
////    //m_pRender->GetCommandList()->SetGraphicsRootConstantBufferView(0, m_Buffer->Resource()->GetGPUVirtualAddress());
////
////    //m_pRender->GetCommandList()->DrawIndexedInstanced(m_boxGeometry->boxGeo->DrawArgs["box"].IndexCount, 1, 0, 0, 0);
////
////
////
////}
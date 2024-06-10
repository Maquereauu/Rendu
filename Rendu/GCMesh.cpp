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

MeshGeometry* GCMesh::GetBoxGeometry()
{
    return m_boxGeo;
}

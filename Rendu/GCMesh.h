#pragma once

//struct SubmeshGeometry
//{
//    UINT IndexCount = 0;
//    UINT StartIndexLocation = 0;
//    INT BaseVertexLocation = 0;
//
//    // Bounding box of the geometry defined by this submesh. 
//    // This is used in later chapters of the book.
//    DirectX::BoundingBox Bounds;
//};

struct MeshBufferData
{
    // Give it a name so we can look it up by name.
    std::string Name;

    // System memory copies.  Use Blobs because the vertex/index format can be generic.
    // It is up to the client to cast appropriately.  
    ID3DBlob* VertexBufferCPU = nullptr;
    ID3DBlob* IndexBufferCPU = nullptr;

    ID3D12Resource* VertexBufferGPU = nullptr;
    ID3D12Resource* IndexBufferGPU = nullptr;

    ID3D12Resource* VertexBufferUploader = nullptr;
    ID3D12Resource* IndexBufferUploader = nullptr;

    // Data about the buffers.
    UINT VertexByteStride = 0;
    UINT VertexBufferByteSize = 0;
    DXGI_FORMAT IndexFormat = DXGI_FORMAT_R16_UINT;
    UINT IndexBufferByteSize = 0;

    // A MeshGeometry may store multiple geometries in one vertex/index buffer.
    // Use this container to define the Submesh geometries so we can draw
    // the Submeshes individually.
    /*std::unordered_map<std::string, SubmeshGeometry> DrawArgs;*/
    UINT IndexCount = 0;

    D3D12_VERTEX_BUFFER_VIEW VertexBufferView()const
    {
        D3D12_VERTEX_BUFFER_VIEW vbv;
        vbv.BufferLocation = VertexBufferGPU->GetGPUVirtualAddress();
        vbv.StrideInBytes = VertexByteStride;
        vbv.SizeInBytes = VertexBufferByteSize;

        return vbv;
    }

    D3D12_INDEX_BUFFER_VIEW IndexBufferView()const
    {
        D3D12_INDEX_BUFFER_VIEW ibv;
        ibv.BufferLocation = IndexBufferGPU->GetGPUVirtualAddress();
        ibv.Format = IndexFormat;
        ibv.SizeInBytes = IndexBufferByteSize;

        return ibv;
    }

    // We can free this memory after we finish upload to the GPU.
    void DisposeUploaders()
    {
        VertexBufferUploader = nullptr;
        IndexBufferUploader = nullptr;
    }
};
struct GCVERTEX
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT4 Color;

	GCVERTEX() : Pos(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f)), Color(DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)) {}

	GCVERTEX(const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT4& color) : Pos(position), Color(color) {}
};

struct GCVERTEXTEXTURE
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT2 TexC; // Uv

	GCVERTEXTEXTURE() : Pos(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f)), TexC(DirectX::XMFLOAT2(0.0f, 0.0f)) {}

	GCVERTEXTEXTURE(const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT2& texCoord) : Pos(position), TexC(texCoord) {}
};

struct ShaderCB {
};

struct WorldCB : ShaderCB {
    DirectX::XMFLOAT4X4 world; // Matrice du monde
};

struct LightAndWorld : ShaderCB {
    DirectX::XMFLOAT4X4 world; // Matrice du monde
    DirectX::XMFLOAT4X4 light; // Matrice du monde
    DirectX::XMFLOAT4X4 normal;
};

//
struct CameraCB {
    DirectX::XMFLOAT4X4 view; // Matrice de vue
    DirectX::XMFLOAT4X4 proj; // Matrice de projection
};



class GCMesh
{
public:
	GCMesh();
    ~GCMesh();

    void Initialize(GCRender* pRender);

    template<typename VertexType>
    void UploadGeometryData(GCGeometry* pGeometry);

    void UploadGeometryDataColor(GCGeometry* pGeometry);
    void UploadGeometryDataTexture(GCGeometry* pGeometry);

    

    template<typename ShaderType>
    void Initialize(GCRender* pRender) {
        m_pRender = pRender;
        //m_pObjectCB = new UploadBuffer<ShaderType>(m_pRender->Getmd3dDevice(), 1, true);
        m_pObjectCB = new SUploadBuffer<ShaderType>(m_pRender->Getmd3dDevice(), 1, true);
        m_pCameraCB = new UploadBuffer<CameraCB>(m_pRender->Getmd3dDevice(), 1, true);


    }

    template<typename T>
    void UpdateObjectBuffer(const T& objectData)
    {
        m_pObjectCB->CopyData(0, objectData);
    }


    // Update Constant Buffer
    //void UpdateObjectBuffer(DirectX::XMMATRIX worldMatrix);
    void UpdateCameraBuffer(DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX projMatrix);



    // Getter
    inline MeshBufferData* GetBufferGeometryData() { return  m_pBufferGeometryData; }
    //inline UploadBuffer<ObjectConstants>* GetConstantBufferData() { return  m_Buffer; }


        //inline UploadBuffer<WorldCB>* GetObjectCBData() { return  m_pObjectCB; }
    SUploadBufferBase* GetObjectCBData() {
        return m_pObjectCB;
    }

    UploadBuffer<CameraCB>* GetCameraCBData() {
        return m_pCameraCB;
    }



private:
    GCRender* m_pRender;

    //Buffer Data #TODO -> Change structure name
    MeshBufferData* m_pBufferGeometryData;

    // #TODO Put this in shader or Other place
    SUploadBufferBase* m_pObjectCB;
    UploadBuffer<CameraCB>* m_pCameraCB;



    ID3D12Resource* CreateDefaultBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList, const void* initData, UINT64 byteSize, ID3D12Resource* uploadBuffer);
};


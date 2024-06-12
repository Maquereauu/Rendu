#pragma once
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
    virtual ~ShaderCB() = default;
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
    inline MeshGeometry* GetBufferGeometryData() { return  m_pBufferGeometryData; }
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
    MeshGeometry* m_pBufferGeometryData;

    //UploadBuffer<WorldCB>* m_pObjectCB;
    SUploadBufferBase* m_pObjectCB;
    UploadBuffer<CameraCB>* m_pCameraCB;



    ID3D12Resource* CreateDefaultBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList, const void* initData, UINT64 byteSize, ID3D12Resource* uploadBuffer);
};


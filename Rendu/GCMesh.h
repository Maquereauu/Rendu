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

    // Update Constant Buffer
    void UpdateObjectBuffer(DirectX::XMMATRIX worldMatrix);
    void UpdateCameraBuffer(DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX projMatrix);



    // Getter
    inline MeshGeometry* GetBufferGeometryData() { return  m_pBufferGeometryData; }
    //inline UploadBuffer<ObjectConstants>* GetConstantBufferData() { return  m_Buffer; }

    inline UploadBuffer<ObjectCB>* GetObjectCBData() { return  m_pObjectCB; }
    inline UploadBuffer<CameraCB>* GetCameraCBData() { return  m_pCameraCB; }



private:
    GCRender* m_pRender;

    //Buffer Data #TODO -> Change structure name
    MeshGeometry* m_pBufferGeometryData;
    //Constant buffer -> WORLD - VIEW - PROJ
    //UploadBuffer<ObjectConstants>* m_Buffer;

    //struct WorldCB {
    //    DirectX::XMFLOAT4X4 world; // Matrice du monde
    //};

    //struct ViewProjCB {
    //    DirectX::XMFLOAT4X4 view; // Matrice de vue
    //    DirectX::XMFLOAT4X4 proj; // Matrice de projection
    //};

    UploadBuffer<ObjectCB>* m_pObjectCB;
    UploadBuffer<CameraCB>* m_pCameraCB;



    ID3D12Resource* CreateDefaultBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList, const void* initData, UINT64 byteSize, ID3D12Resource* uploadBuffer);
};


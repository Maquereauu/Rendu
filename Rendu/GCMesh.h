#pragma once
struct GCVERTEX
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT4 Color;
};

struct GCVERTEXTEXTURE
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT2 TexC; // Normal
};



class GCMesh
{
public:
	GCMesh();
	~GCMesh();

	void Initialize(GCRender* pRender);
	void Render();

	//void UploadWorldViewProjData();

	void UploadGeometryDataColor(GCGeometry* pGeometry);
	void UploadGeometryDataTexture(GCGeometry* pGeometry);


	//DirectX::XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
	//DirectX::XMFLOAT4X4 mView = MathHelper::Identity4x4();
	//DirectX::XMFLOAT4X4 mProj = MathHelper::Identity4x4();
	//std::unique_ptr<UploadBuffer<ObjectConstants>> m_Buffer;

	// Primitive
	void CreateBoxGeometryColor();
	void CreateBoxGeometryTexture();
	//// Parse
	void CreateObjGeometryColor();
	void CreateObjGeometryTexture();
	void SetWorldMatrix(DirectX::XMMATRIX world);
	MeshGeometry* GetBoxGeometry();
	//GCGeometry* GetGeometryTexture();
	//std::unique_ptr<UploadBuffer<ObjectConstants>> m_Buffer;
	//DirectX::XMMATRIX m_World;


	MeshGeometry* m_boxGeo;

private:

	GCRender* m_pRender;
};
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

class GCGeo {
public:
	virtual ~GCGeo() {}


	std::vector<std::uint16_t> indices;
	std::size_t vertexNumber;
	std::size_t indiceNumber;
	std::vector<DirectX::XMFLOAT3> pos;
	std::vector<DirectX::XMFLOAT4> color;
	std::vector<DirectX::XMFLOAT2> texC;
	SubmeshGeometry submesh;
	std::unique_ptr<MeshGeometry> boxGeo;
};



class GCGeometry
{
public:
	GCGeometry();
	~GCGeometry();

	void Initialize(GCRender* pRender);
	void Render();

	//void UploadWorldViewProjData();

	void UploadGeometryDataColor();
	void UploadGeometryDataTexture();

	void CreatePrimitiveGeometry(int id);
	void CreateObjGeometry(std::wstring obj, bool isTextured = false);

	//DirectX::XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
	//DirectX::XMFLOAT4X4 mView = MathHelper::Identity4x4();
	//DirectX::XMFLOAT4X4 mProj = MathHelper::Identity4x4();
	//std::unique_ptr<UploadBuffer<ObjectConstants>> m_Buffer;



	GCGeometry* GetBoxGeometry();
	//GCGeometry* GetGeometryTexture();



private:
	// Primitive
	void CreateBoxGeometryColor(int id);
	void CreateBoxGeometryTexture(int id);
	//// Parse
	void CreateObjGeometryColor(std::wstring obj);
	void CreateObjGeometryTexture(std::wstring obj);

	GCRender* m_pRender;

	GCGeo* m_pGeometry;
};


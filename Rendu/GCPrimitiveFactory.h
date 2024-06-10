#pragma once

class PrimitiveFactory
{
public:

	PrimitiveFactory();
	~PrimitiveFactory();
	void Initialize(int type, GCRender* pRender);

	GCGeometry* BuildBoxGeometryColor();
	GCGeometry* BuildBoxGeometryTexture();

	GCGeometry* BuildPrimitive(std::wstring name, bool hasTexture);
	// 
	//void BuildSphereGeometry();
protected:

	//int m_Type;
	//GCGEOMETRY m_BoxGeometry;
	//Geometry m_SphereGeometry;

	GCRender* m_pRender;
	std::map < std::wstring, std::map<
		std::wstring, std::variant<std::vector<uint16_t>, std::vector<DirectX::XMFLOAT2>, std::vector<DirectX::XMFLOAT3>, std::vector<DirectX::XMFLOAT4>
		>>> m_primitiveInfos;
};


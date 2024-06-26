#pragma once

class GCPrimitiveFactory
{
public:



	GCPrimitiveFactory();
	~GCPrimitiveFactory();
  void Initialize();
	/*GCGeometry* BuildBoxGeometryColor();
	GCGeometry* BuildBoxGeometryTexture();*/
	GCGeometry* BuildGeometryColor(std::wstring name, DirectX::XMFLOAT4 color);
	GCGeometry* BuildGeometryTexture(std::wstring name);
  
private:

	GCRender* m_pRender;
	std::map < std::wstring, std::map<
		std::wstring, std::variant<std::vector<uint16_t>, std::vector<DirectX::XMFLOAT2>, std::vector<DirectX::XMFLOAT3>, std::vector<DirectX::XMFLOAT4>
		>>> m_primitiveInfos;
};


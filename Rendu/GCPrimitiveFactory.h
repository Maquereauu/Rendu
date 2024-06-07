#pragma once

class PrimitiveFactory
{
public:

	PrimitiveFactory();
	~PrimitiveFactory();
	void Initialize(int type, GCRender* pRender);

	GCGeo* BuildBoxGeometryColor();
	GCGeo* BuildBoxGeometryTexture();

	// 
	//void BuildSphereGeometry();
protected:

	//int m_Type;
	//GCGEOMETRY m_BoxGeometry;
	//Geometry m_SphereGeometry;

	GCRender* m_pRender;
};


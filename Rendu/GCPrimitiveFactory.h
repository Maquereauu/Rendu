#pragma once

class GCPrimitiveFactory
{
public:

	GCPrimitiveFactory();
	~GCPrimitiveFactory();
	void Initialize(int type, GCRender* pRender);

	GCGeometry* BuildBoxGeometryColor();
	GCGeometry* BuildBoxGeometryTexture();

protected:

	GCRender* m_pRender;
};


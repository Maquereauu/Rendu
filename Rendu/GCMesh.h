#pragma once
class GCMesh
{
public:
	GCMesh();
	~GCMesh();
	void Initialize(GCRender* pRender);

private:
	GCGeometry m_geo;
};


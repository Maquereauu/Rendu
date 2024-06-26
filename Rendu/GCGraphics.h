#pragma once

#define FLAG_COORDS 0x01
#define FLAG_UV 0x02


//
//class GCGeometry;
//class GCMesh;

//#include "GCMesh.h"

class GCGraphics
{
public:
	GCGraphics();

	void Initialize(Window* window);


	// Principal Object Creation

	GCShader* CreateShaderColor();
	GCShader* CreateShaderTexture();
	//GCShader* CreateShaderCustom(HLSLFile* customShaderFile);


	GCMaterial* CreateMaterial();
	GCMesh* CreateMesh(GCGeometry* pGeometry);

	template<typename T>
	GCMesh* CreateMeshh(GCGeometry* pGeometry);

	GCTexture* CreateTexture(std::string fileName);


	//Delete
	void RemoveShader(GCShader* pShader);
	void RemoveMaterial(GCMaterial* pMaterial);
	void RemoveMesh(GCMesh* pMesh);
	void RemoveTexture(GCTexture* pTexture);


	//// Resources Manager
	std::vector<GCShader*> GetShaders();
	std::vector<GCMaterial*> GetMaterials();
	std::vector<GCMesh*> GetMeshes();
	std::vector<GCTexture*> GetTextures();

	// Id
	int GetTextureId() const { return m_textureId; }


	// Render
	GCRender* GetRender() const { return m_pRender; }



	GCPrimitiveFactory* GetPrimitiveFactory() const {return m_pPrimitiveFactory;}
	GCModelParserObj* GetModelParserFactory() const {return m_pModelParserFactory;}



private:
	// Render instance contain Window
	GCRender* m_pRender;

	int m_meshId = 0;
	int m_shaderId = 0;
	int m_materialId = 0;
	int m_textureId = 0;

	std::vector<GCTexture*> m_vTextures;
	std::vector<GCShader*> m_vShaders;
	std::vector<GCMaterial*> m_vMaterials;
	std::vector<GCMesh*> m_vMeshes;

	// Mesh
	GCPrimitiveFactory* m_pPrimitiveFactory;
	GCModelParserObj* m_pModelParserFactory;







};
template<typename T>
GCMesh* GCGraphics::CreateMeshh(GCGeometry* pGeometry)
{
	GCMesh* mesh = new GCMesh();
	mesh->Initialize<T>(m_pRender);

	if (pGeometry->texC.size() == 0)
		mesh->UploadGeometryDataColor(pGeometry);
	else
		mesh->UploadGeometryDataTexture(pGeometry);

	m_vMeshes.push_back(mesh);
	return mesh;
}


#pragma once

#define FLAG_COORDS 0x01
#define FLAG_UV 0x02

class GCGraphics
{
public:
	GCGraphics();

	void Initialize(Window* window);


	// Principal Object Creation
	GCShader* CreateShader(int type, std::wstring hlsl);
	GCMaterial* CreateMaterial();
	GCMesh* CreateMesh(GCGeometry* pGeometry);
	GCTexture* CreateTexture(std::string fileName);
	//Delete
	void DeleteShader(GCShader* pShader);
	void DeleteMaterial(GCMaterial* pMaterial);
	void DeleteMesh(GCMesh* pMesh);
	void DeleteTexture(GCTexture* pTexture);
	//// Resources Manager
	std::vector<GCShader*> GetShaders();
	std::vector<GCMaterial*> GetMaterials();
	std::vector<GCMesh*> GetMeshes();
	std::vector<GCTexture*> GetTextures();

	GCRender* GetRender() const { return m_pRender; }
	int GetTexId() const { return m_textureId; }

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






};


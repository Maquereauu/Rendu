#include "framework.h"


GCGraphics::GCGraphics() {
    m_pRender = nullptr;
}

void GCGraphics::Initialize(Window* window) {
    m_pRender = new GCRender();
    m_pRender->Initialize(this,window);

    // 
    m_pPrimitiveFactory = new GCPrimitiveFactory();
    m_pModelParserFactory = new GCModelParserObj();
}


GCMesh* GCGraphics::CreateMesh(GCGeometry* pGeometry) {
    GCMesh* mesh = new GCMesh();
    mesh->Initialize(m_pRender);
    if(pGeometry->texC.size() == 0)        
    {
        mesh->UploadGeometryDataColor(pGeometry);
    }
    else {
        mesh->UploadGeometryDataTexture(pGeometry);
    }
    m_vMeshes.push_back(mesh);
    return mesh;
}



GCTexture* GCGraphics::CreateTexture(std::string fileName) {
	GCTexture* texture = new GCTexture();
	texture->Initialize(fileName, this);
    m_vTextures.push_back(texture);
	return texture;
}


GCShader* GCGraphics::CreateShader(int type) {
    GCShader* shader;

    switch (type) {
    default:
    {
        shader = new GCShader();
        return shader;
        break;
    }
    case 0:
    {
        shader = new GCShaderColor();
        shader->SetType(0);
        shader->Initialize(m_pRender, L"color");
        m_vShaders.push_back(shader);
        m_shaderId++;
        return shader;
        break;
    }
    case 1:
    {
        shader = new GCShaderTexture();
        shader->SetType(1);
        shader->Initialize(m_pRender, L"texture");
        m_vShaders.push_back(shader);
        m_shaderId++;
        return shader;
        break;
    }
    }

    //GCShader* parentShader = dynamic_cast<GCShader*>(shader);
    //if (parentShader != nullptr) {
    //    return parentShader;
    //}
    //else {
    //    return nullptr;
    //}
}

GCMaterial* GCGraphics::CreateMaterial() {
    GCMaterial* material = new GCMaterial();
    //material->Initialize();
    //m_vMaterials.push_back(material);
    //m_materialId++;
    return material;
}

std::vector<GCShader*> GCGraphics::GetShaders() {
    return m_vShaders;
}

std::vector<GCMaterial*> GCGraphics::GetMaterials() {
    return m_vMaterials;
}

std::vector<GCMesh*> GCGraphics::GetMeshes() {
    return m_vMeshes;
}

std::vector<GCTexture*> GCGraphics::GetTextures() {
    return m_vTextures;
}

void GCGraphics::DeleteShader(GCShader* pShader) {
    auto it = std::find(m_vShaders.begin(), m_vShaders.end(), pShader);

    if (it != m_vShaders.end()) {
        m_vShaders.erase(it);
    }

    delete pShader;
}

void GCGraphics::DeleteMaterial(GCMaterial* pMaterial) {
    auto it = std::find(m_vMaterials.begin(), m_vMaterials.end(), pMaterial);

    if (it != m_vMaterials.end()) {
        m_vMaterials.erase(it);
    }

    delete pMaterial;
}
void GCGraphics::DeleteMesh(GCMesh* pMesh) {
    auto it = std::find(m_vMeshes.begin(), m_vMeshes.end(), pMesh);

    if (it != m_vMeshes.end()) {
        m_vMeshes.erase(it);
    }
    delete pMesh;
}
void GCGraphics::DeleteTexture(GCTexture* pTexture) {
    auto it = std::find(m_vTextures.begin(), m_vTextures.end(), pTexture);

    if (it != m_vTextures.end()) {
        m_vTextures.erase(it);
    }

    delete pTexture;
}
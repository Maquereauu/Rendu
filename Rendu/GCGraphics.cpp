#include "framework.h"
GCGraphics::GCGraphics() {
    m_pRender = nullptr;
}

void GCGraphics::Initialize(Window* window) {
    m_pRender = new GCRender();
    m_pRender->Initialize(this,window);
}

//void Graphics::Initialize() {
//	// Init Debug Console
//	//AllocConsole();
//	//FILE* fp;
//	//freopen_s(&fp, "CONOUT$", "w", stdout);
//	//freopen_s(&fp, "CONIN$", "r", stdin);
//	//std::cout << "Console initialized!" << std::endl;
//
//	// Init render
//
//
//
//}

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


GCShader* GCGraphics::CreateShader(int type, std::wstring hlsl) {
    GCShader* shader = nullptr; // Initialisation de la variable shader à nullptr

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
        shader->m_Type = 0;
        shader->Initialize(m_pRender, hlsl);
        m_vShaders.push_back(shader);
        m_shaderId++;
        return shader;
        break;
    }
    case 1:
    {
        shader = new GCShaderTexture();
        shader->m_Type = 1;
        shader->Initialize(m_pRender, hlsl);
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


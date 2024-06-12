#include "framework.h"

std::string readShaderFile(const std::string& filePath) {
	std::ifstream file(filePath);
	std::stringstream buffer;
	if (file) {
		buffer << file.rdbuf();
		file.close();
		return buffer.str();
	}
	else {
		std::cerr << "Erreur : Impossible de lire le fichier " << filePath << std::endl;
		return "";
	}
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{

	AllocConsole(); // Crée une nouvelle console associée à ce processus

	FILE* stream;
	freopen_s(&stream, "CONOUT$", "w", stdout); // Redirige la sortie standard vers la console

	std::cout << "This works" << std::endl; // Affiche du texte dans la console

	std::string shaderCode = readShaderFile("Shaders/color.hlsl");
	if (!shaderCode.empty()) {
		std::cout << "Contenu du shader : " << std::endl;
		std::cout << shaderCode << std::endl;
	}


	Window* window = new Window(hInstance);
	window->Initialize();

	GCGraphics* graphics = new GCGraphics();
	graphics->Initialize(window);

	graphics->GetPrimitiveFactory()->Initialize();

	// Geometry (Resource)
	GCGeometry* geo = graphics->GetPrimitiveFactory()->BuildGeometryColor(L"cube", DirectX::XMFLOAT4(DirectX::Colors::White));
	GCGeometry* geo1 = graphics->GetModelParserFactory()->BuildObjTexture("monkeyUv.obj");

	///// Create Render Resources
	graphics->GetRender()->ResetCommandList(); // Reset Command List Before Resources Creation


	// Mesh
	GCMesh* mesh = graphics->CreateMesh(geo);
	GCMesh* mesh1 = graphics->CreateMesh(geo1);
	GCShader* shader1 = graphics->CreateShaderColor();
	GCShader* shader2 = graphics->CreateShaderTexture();
	GCTexture* tex1 = graphics->CreateTexture("texture");

	graphics->GetRender()->CloseCommandList(); // Close and Execute after creation
	graphics->GetRender()->ExecuteCommandList();// Close and Execute after creation

	///// 

	// SET CAMERA 
	DirectX::XMMATRIX projection = DirectX::XMMatrixPerspectiveFovLH(0.25f * MathHelper::Pi, window->AspectRatio(), 1.0f, 1000.0f);

	DirectX::XMVECTOR cameraPosition = DirectX::XMVectorSet(0.0f, -10.0f, 5.0f, 1.0f);
	DirectX::XMVECTOR targetPosition = DirectX::XMVectorZero();
	DirectX::XMVECTOR upVector = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH(cameraPosition, targetPosition, upVector);

	// SET CAMERA


	DirectX::XMFLOAT4X4 I(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		3.0f, 0.0f, 0.0f, 1.0f);




	graphics->GetRender()->PrepareDraw();



	graphics->GetRender()->DrawOneObject(mesh1, shader2, tex1, MathHelper::Identity4x4(), projection, viewMatrix);
	graphics->GetRender()->DrawOneObject(mesh, shader1, nullptr, I, projection, viewMatrix);


	graphics->GetRender()->PostDraw();

	//graphics->GetRender()->PrepareDraw();

	//graphics->GetRender()->PostDraw();


	window->Run(graphics->GetRender());

}


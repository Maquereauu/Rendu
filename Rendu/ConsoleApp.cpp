#include "framework.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{

	Window* window = new Window(hInstance);
	window->Initialize();

	GCGraphics* graphics = new GCGraphics();
	graphics->Initialize(window);

	// Geometry (Resource)
	GCGeometry* geo = graphics->GetPrimitiveFactory()->BuildBoxGeometryColor();
	GCGeometry* geo1 = graphics->GetModelParserFactory()->BuildObjTexture("monkeyUv.obj");
	GCShader* shader1 = graphics->CreateShader(STEnum::color);
	GCShader* shader2 = graphics->CreateShader(STEnum::texture);

	///// Create Render Resources
	graphics->GetRender()->ResetCommandList(); // Reset Command List Before Resources Creation

	shader1->Load();
	shader2->Load();
	// Mesh
	GCMesh* mesh = graphics->CreateMesh(geo);
	GCMesh* mesh1 = graphics->CreateMesh(geo1);
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


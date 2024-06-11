#include "framework.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{


	/*DebugOutput("App started");*/
	Window* window = new Window(hInstance);
	window->Initialize();
	//SetWindow(window);

	GCGraphics* graphics = new GCGraphics();
	graphics->Initialize(window);


	GCModelParserObj* ModelParser = new GCModelParserObj();
	ModelParser->Initialize(graphics->GetRender(), "monkeyUv.obj");
	ModelParser->ParseObj();


	GCPrimitiveFactory* primFact = new GCPrimitiveFactory();
	GCGeometry* geo = primFact->BuildBoxGeometryColor();


	GCGeometry* geo1 = ModelParser->BuildObjTexture();


	graphics->GetRender()->ResetCommandList(); // Reset Command List Before Resources Creation


	GCMesh* mesh = graphics->CreateMesh(geo);
	GCMesh* mesh1 = graphics->CreateMesh(geo1);
	GCShader* shader1 = graphics->CreateShader(STEnum::color, L"color");
	GCShader* shader2 = graphics->CreateShader(STEnum::texture, L"texture");
	GCTexture* tex1 = graphics->CreateTexture("texture");

	graphics->GetRender()->CloseCommandList(); // Close and Execute after creation
	graphics->GetRender()->ExecuteCommandList();// Close and Execute after creation


	DirectX::XMFLOAT4X4 I(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);




	graphics->GetRender()->PrepareDraw();
	graphics->GetRender()->DrawOneObject(mesh1, shader2, tex1, MathHelper::Identity4x4());
	graphics->GetRender()->DrawOneObject(mesh, shader1, nullptr, I);
	graphics->GetRender()->PostDraw();

	window->Run(graphics->GetRender());

}


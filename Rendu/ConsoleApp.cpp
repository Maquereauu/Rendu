#include "framework.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{


	/*DebugOutput("App started");*/
	Window* window = new Window(hInstance);
	window->Initialize();
	//SetWindow(window);

	GCGraphics* graphics = new GCGraphics();
	graphics->Initialize(window);

	graphics->GetRender()->ResetCommandList();

	GCModelParserObj* ModelParser = new GCModelParserObj();
	ModelParser->Initialize(graphics->GetRender(), "monkeyUv.obj");
	ModelParser->ParseObj();
	PrimitiveFactory* primFact = new PrimitiveFactory();

	GCGeometry* geo = primFact->BuildBoxGeometryColor();
	GCGeometry* geo1 = ModelParser->BuildObjTexture();

	GCMesh* mesh = graphics->CreateMesh(geo);
	GCMesh* mesh1 = graphics->CreateMesh(geo1);
	GCShader* shader1 = graphics->CreateShader(STEnum::color, L"color");
	GCShader* shader2 = graphics->CreateShader(STEnum::texture, L"texture");

	//GCMaterial* material1 = graphics->CreateMaterial();
	//material1->AddTexture("ahah", graphics);


	GCTexture* tex1 = graphics->CreateTexture("texture");

	graphics->GetRender()->CloseCommandList();
	graphics->GetRender()->ExecuteCommandList();
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


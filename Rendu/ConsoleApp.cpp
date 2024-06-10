//#include <iostream>
#include "framework.h"

//void DebugOutput(const std::string& message)
//{
//	OutputDebugString(L"Salut");
//	OutputDebugString(L"\n");
//}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{


	/*DebugOutput("App started");*/
	Window* window = new Window(hInstance);
	window->Initialize();
	//SetWindow(window);

	GCGraphics* graphics = new GCGraphics();
	graphics->Initialize(window);

	graphics->m_pRender->ResetCommandList();

	PrimitiveFactory* primFact = new PrimitiveFactory();

	GCGeometry* geo = primFact->BuildBoxGeometryColor();

	GCMesh* mesh = graphics->CreateMesh(geo);
	GCShader* shader1 = graphics->CreateShader(STEnum::color, L"color");
	GCShader* shader2 = graphics->CreateShader(STEnum::texture, L"texture");

	//GCMaterial* material1 = graphics->CreateMaterial();
	//material1->AddTexture("ahah", graphics);


	//GCTexture* tex1 = graphics->CreateTexture("ahah");

	graphics->m_pRender->CloseCommandList();
	graphics->m_pRender->ExecuteCommandList();

	//graphics->m_pRender->ResetCommandList();
	//graphics->m_pRender->CloseCommandList();
	//graphics->m_pRender->ExecuteCommandList();


	//graphics->m_pRender->ResetCommandList();

	graphics->m_pRender->PrepareDraw();
	graphics->m_pRender->DrawOneObject(mesh, shader1, nullptr, MathHelper::Identity4x4());
	graphics->m_pRender->PostDraw();

	//GCRender* render = new GCRender();
	////SetRender(render);
	//render->Initialize();

	window->Run(graphics->m_pRender);

}


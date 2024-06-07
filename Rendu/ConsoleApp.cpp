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


	GCRender* render = new GCRender();
	render->Initialize();
	/*graphics->Initialize();*/


	render->ResetCommandList();

	/*GCMesh* mesh = graphics->CreateMesh();
	GCShader* shader1 = graphics->CreateShader(STEnum::color, L"color");
	GCShader* shader2 = graphics->CreateShader(STEnum::texture, L"texture");*/

	//GCMaterial* material1 = graphics->CreateMaterial();
	//material1->AddTexture("ahah", graphics);

	//graphics->CreateTexture("ahah");


	render->CloseCommandList();
	render->ExecuteCommandList();


	//GCRender* render = new GCRender();
	////SetRender(render);
	//render->Initialize();

	window->Run(render);

}


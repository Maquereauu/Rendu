// header.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclure les en-têtes Windows rarement utilisés
// Fichiers d'en-tête Windows
#include <windows.h>
// Fichiers d'en-tête C RunTime
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "Timer.h"
#include <wrl.h>
#include <dxgi1_4.h>
#include <d3d12.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>
#include <string>
#include <memory>
#include <algorithm>
#include <vector>
#include <array>
#include <unordered_map>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <cassert>
#include "d3dx12.h"
#include <WindowsX.h>
#include "MathHelper.h"
#include "d3dUtil.h"
#include <wrl/client.h>
#include <dxgi1_4.h>
#include <d3d12.h>
#include <iostream>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include "d3dx12.h"
#include "DDSTextureLoader.h"
#include "Window.h"
//#include "GCGraphics.h"
#include "GCRender.h"
#include "GCShader.h"
#include "GCGeometry.h"
#include "GCMaterial.h"
#include "GCMesh.h"
#include "GCModelParser.h"
#include "GCModelParserObj.h"
#include "GCPrimitiveFactory.h"
#include "GCShaderColor.h"
#include "GCShaderTexture.h"
#include "GCTexture.h"
#include "GCTextureFactory.h"
#include "Global.h"
#include "ShaderTypeEnum.h"
#include "Timer.h"
#include "UploadBuffer.h"
#include "PrimitiveTypeEnum.h"
class GCGeometry;
class GCGraphics;
class GCMaterial;
class GCMesh;
class GCModelParser;
class GCModelParserObj;
class GCPrimitiveFactory;
class GCRender;
class GCShader;
class GCShaderColor;
class GCShaderTexture;
class GCTexture;
class GCTextureFactory;
class MathHelper;
class Timer;
class Window;
#pragma once

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include "targetver.h"
//#define WIN32_LEAN_AND_MEAN             // Exclure les en-têtes Windows rarement utilisés
// Fichiers d'en-tête Windows
#include <windows.h>

// Fichiers d'en-tête C RunTime
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "Timer.h"
#include <string>
#include <map>
#include <variant>
#include <memory>
#include <algorithm>
#include <vector>
#include <array>
#include <unordered_map>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <cassert>
#include <iostream>

#include <wrl.h>
#include <dxgi1_4.h>
#include <d3d12.h>
#include <d3d11_1.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>
#include <wrl/client.h>
#include <WindowsX.h>





struct HLSLFile;
struct GCGeometry;

struct MeshBufferData;
struct GCVERTEX;
struct GCVERTEXTEXTURE;
struct ShaderCB;
struct WorldCB;
struct LightAndWorld;
struct CameraCB;

//template<typename T>;

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
class GCShaderCustom;
class GCTexture;
class GCTextureFactory;
class SUploadBufferBase; // 
//class SUploadBuffer; 
class MathHelper;
class Timer;
class Window;

#include "d3dx12.h"
#include "DDSTextureLoader.h"
#include "MathHelper.h"

#include "d3dx12.h"
#include "Window.h"
#include "GCRender.h"
#include "UploadBuffer.h"
#include "GCGeometry.h"
#include "GCMesh.h"
#include "GCShader.h"
#include "GCMaterial.h"
#include "GCModelParser.h"
#include "GCModelParserObj.h"
#include "GCPrimitiveFactory.h"
#include "GCShaderColor.h"
#include "GCShaderTexture.h"
#include "GCShaderCustom.h"
#include "GCTexture.h"
#include "GCGraphics.h"
#include "GCTextureFactory.h"
#include "ShaderTypeEnum.h"
#include "Timer.h"
#include "PrimitiveTypeEnum.h"

#include "HLSLReader.h"


#include "framework.h"

PrimitiveFactory::PrimitiveFactory() {
}

PrimitiveFactory::~PrimitiveFactory() {
}

void PrimitiveFactory::Initialize(int type, GCRender* pRender)
{
	m_pRender = pRender;
}

GCGeometry* PrimitiveFactory::BuildBoxGeometryColor()
{
	GCGeometry* boxGeometry = new GCGeometry();

	boxGeometry->pos = {
		{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f) },
		{ DirectX::XMFLOAT3(-1.0f, +1.0f, -1.0f) },
		{ DirectX::XMFLOAT3(+1.0f, +1.0f, -1.0f) },
		{ DirectX::XMFLOAT3(+1.0f, -1.0f, -1.0f) },
		{ DirectX::XMFLOAT3(-1.0f, -1.0f, +1.0f) },
		{ DirectX::XMFLOAT3(-1.0f, +1.0f, +1.0f) },
		{ DirectX::XMFLOAT3(+1.0f, +1.0f, +1.0f) },
		{ DirectX::XMFLOAT3(+1.0f, -1.0f, +1.0f) },
	};

	boxGeometry->color = {
	{ DirectX::XMFLOAT4(DirectX::Colors::White) },
	{  DirectX::XMFLOAT4(DirectX::Colors::Black) },
	{ DirectX::XMFLOAT4(DirectX::Colors::Red) },
	{  DirectX::XMFLOAT4(DirectX::Colors::Green) },
	{  DirectX::XMFLOAT4(DirectX::Colors::Blue) },
	{  DirectX::XMFLOAT4(DirectX::Colors::Yellow) },
	{ DirectX::XMFLOAT4(DirectX::Colors::Cyan) },
	{ DirectX::XMFLOAT4(DirectX::Colors::Magenta) },
	};


	boxGeometry->indices = {
		0, 1, 2, 0, 2, 3,
		4, 6, 5, 4, 7, 6,
		4, 5, 1, 4, 1, 0,
		3, 2, 6, 3, 6, 7,
		1, 5, 6, 1, 6, 2,
		4, 0, 3, 4, 3, 7,
	};

	boxGeometry->vertexNumber = boxGeometry->pos.size();
	boxGeometry->indiceNumber = boxGeometry->indices.size();



	return boxGeometry;
}


GCGeometry* PrimitiveFactory::BuildBoxGeometryTexture()
{
	GCGeometry* boxGeometry = new GCGeometry();

	boxGeometry->pos = {
		 DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f),
		 DirectX::XMFLOAT3(-1.0f, +1.0f, -1.0f),
		 DirectX::XMFLOAT3(+1.0f, +1.0f, -1.0f),
		 DirectX::XMFLOAT3(+1.0f, -1.0f, -1.0f),

		 DirectX::XMFLOAT3(-1.0f, -1.0f, +1.0f),
		 DirectX::XMFLOAT3(-1.0f, +1.0f, +1.0f),
		 DirectX::XMFLOAT3(+1.0f, +1.0f, +1.0f),
		 DirectX::XMFLOAT3(+1.0f, -1.0f, +1.0f),

		 DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f),
		 DirectX::XMFLOAT3(-1.0f, +1.0f, -1.0f),
		 DirectX::XMFLOAT3(-1.0f, +1.0f, +1.0f),
		 DirectX::XMFLOAT3(-1.0f, -1.0f, +1.0f),

		 DirectX::XMFLOAT3(+1.0f, -1.0f, -1.0f),
		 DirectX::XMFLOAT3(+1.0f, +1.0f, -1.0f),
		 DirectX::XMFLOAT3(+1.0f, +1.0f, +1.0f),
		 DirectX::XMFLOAT3(+1.0f, -1.0f, +1.0f),

		 DirectX::XMFLOAT3(-1.0f, +1.0f, -1.0f),
		 DirectX::XMFLOAT3(-1.0f, +1.0f, +1.0f),
		 DirectX::XMFLOAT3(+1.0f, +1.0f, +1.0f),
		 DirectX::XMFLOAT3(+1.0f, +1.0f, -1.0f),

		 DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f),
		 DirectX::XMFLOAT3(-1.0f, -1.0f, +1.0f),
		 DirectX::XMFLOAT3(+1.0f, -1.0f, +1.0f),
		 DirectX::XMFLOAT3(+1.0f, -1.0f, -1.0f),
	};
	boxGeometry->texC = {
		DirectX::XMFLOAT2(0, 1),
		DirectX::XMFLOAT2(0, 0),
		DirectX::XMFLOAT2(1, 0),
		DirectX::XMFLOAT2(1, 1),

		DirectX::XMFLOAT2(0, 1),
		DirectX::XMFLOAT2(0, 0),
		DirectX::XMFLOAT2(1, 0),
		DirectX::XMFLOAT2(1, 1),

		DirectX::XMFLOAT2(0, 1),
		DirectX::XMFLOAT2(0, 0),
		DirectX::XMFLOAT2(1, 0),
		DirectX::XMFLOAT2(1, 1),

		DirectX::XMFLOAT2(0, 1),
		DirectX::XMFLOAT2(0, 0),
		DirectX::XMFLOAT2(1, 0),
		DirectX::XMFLOAT2(1, 1),

		DirectX::XMFLOAT2(0, 1),
		DirectX::XMFLOAT2(0, 0),
		DirectX::XMFLOAT2(1, 0),
		DirectX::XMFLOAT2(1, 1),

		DirectX::XMFLOAT2(0, 1),
		DirectX::XMFLOAT2(0, 0),
		DirectX::XMFLOAT2(1, 0),
		DirectX::XMFLOAT2(1, 1),
	};


	boxGeometry->indices =
	{
		// Front face
		0, 1, 2,
		0, 2, 3,

		// Back face
		4, 6, 5,
		4, 7, 6,

		// Left face
		8, 10, 9,
		8, 11, 10,

		// Right face
		12, 13, 14,
		12, 14, 15,

		// Top face
		16, 17, 18,
		16, 18, 19,

		// Bottom face
		20, 22, 21,
		20, 23, 22
	};
	boxGeometry->vertexNumber = boxGeometry->pos.size();
	boxGeometry->indiceNumber = boxGeometry->indices.size();


	return boxGeometry;
}
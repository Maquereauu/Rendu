#pragma once

class GCShaderColor : public GCShader
{
public:

	virtual void Initialize(GCRender* pRender, std::wstring hlslName) override;


	virtual void CompileShader(std::wstring hlsl) override;



};


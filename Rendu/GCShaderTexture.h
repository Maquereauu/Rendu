#pragma once

class GCShaderTexture : public GCShader
{
public:
	virtual void CompileShader(std::wstring hlsl) override;

};


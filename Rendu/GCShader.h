#pragma once

class GCShader
{
public:
	GCShader();
	~GCShader();

	virtual void CompileShader(std::wstring hlsl);

	ID3DBlob* GetmvsByteCode();
	ID3DBlob* GetmpsByteCode();

	void RootSign();
	void Pso();

	ID3D12RootSignature* GetRootSign();
	ID3D12PipelineState* GetPso();

	virtual void Initialize(GCRender* pRender, std::wstring hlslName);
	void Render();

	int GetType() const { return m_Type; }
	void SetType(int type) { m_Type = type;}


	ID3DBlob* CompileShaderBase(const std::wstring& filename, const D3D_SHADER_MACRO* defines, const std::string& entrypoint, const std::string& target);


private:
	ID3D12RootSignature* m_RootSignature = nullptr;
	ID3D12PipelineState* m_PSO = nullptr;
	int m_Type;

protected:


	std::vector<D3D12_INPUT_ELEMENT_DESC> m_InputLayout;
	ID3DBlob* m_vsByteCode = nullptr;
	ID3DBlob* m_psByteCode = nullptr;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
	int m_count = 0;

	// 
	GCRender* m_pRender;
};


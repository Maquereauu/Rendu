#pragma once

struct ObjInfo {
	std::vector<std::vector<float>> coords;
	std::vector<std::vector<uint16_t>> facesInfos;
	std::vector<std::vector<float>> uvs;
};

class GCModelParserObj
{
public:
	GCModelParserObj();
	~GCModelParserObj();
	void Initialize(GCRender* pRender);
	bool ParseObj(std::wstring fileName);

	GCGeometry* BuildObjColor(std::wstring fileName);
	GCGeometry* BuildObjTexture(std::wstring fileName);


private:
	ObjInfo m_ParsedObj;


	GCRender* m_pRender;
	std::string m_fileName;

};


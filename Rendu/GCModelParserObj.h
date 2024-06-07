#pragma once

struct ObjInfo {
	std::vector<std::vector<float>> coords;
	std::vector<std::vector<uint16_t>> facesInfos;
	std::vector<std::vector<float>> uvs;
};

class ModelParserObj
{
public:
	ModelParserObj();
	~ModelParserObj();
	void Initialize(GCRender* pRender, std::string fileName);
	void ParseObj();

	GCGeometry* BuildObjColor();
	GCGeometry* BuildObjTexture();


private:
	ObjInfo m_ParsedObj;
	GCRender* m_pRender;
	std::string m_fileName;
};


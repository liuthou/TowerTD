#include "ModelAttribute.h"
#include "TowerAttribute.h"
USING_NS_CC;
using namespace tinyxml2;

ModelAttribute* ModelAttribute::modelattribute = nullptr;
ModelAttribute* ModelAttribute::getInstance(int modeid){
	if (modelattribute==nullptr)
	{
		modelattribute = new ModelAttribute();
		modelattribute->openXMLFIle("Model.xml");
		modelattribute->parseXML();
	}
	CCASSERT(modelattribute->init(modeid),StringUtils::format("Couldn't found model id:%d",modeid).c_str());
	return modelattribute;
}

//从模型的id查找一个模型的属性map
bool ModelAttribute::init(int modelid){
	this->modelid=modelid;
	auto it = id_map->find(modelid);
	if (it!=id_map->end())
	{
		tmp_attribute_map = it->second;
		return true;
	}
	return false;
}

//给定id,读取保存属性的map后,查找map中的属性值
std::string ModelAttribute::getStringAttribute(int type,std::string defaultvalue){
	if (type==ModelAttributeConfType::Model_Sprite||type==TowerAttributeConfType::Tower_Sprite)
	{
		auto it = tmp_attribute_map.find("Sprite");
		if (it != tmp_attribute_map.end())
		{
			std::string tmpvalue = it->second;
			return tmpvalue;
		}
	}
	if (type==ModelAttributeConfType::Model_Runanimate||type==TowerAttributeConfType::Tower_Runanimate)
	{
		auto it = tmp_attribute_map.find("Runanimate");
		if (it != tmp_attribute_map.end())
		{
			std::string tmpvalue = it->second;
			return tmpvalue;
		}
	}
	if (type==ModelAttributeConfType::Model_Dieanimate||type==TowerAttributeConfType::Tower_Dieanimate)
	{
		auto it = tmp_attribute_map.find("Dieanimate");
		if (it != tmp_attribute_map.end())
		{
			std::string tmpvalue = it->second;
			return tmpvalue;
		}
	}
	return defaultvalue;
}

//解析xml,id为int类型,其它属性为string类型
void ModelAttribute::parseXML(){
	if (xmldocument)
	{
		log("parseXML");
		XMLElement* root = xmldocument->RootElement();
		log("xml get root child element");
		XMLElement* att_element = root->FirstChildElement("Model");
		log("xml get first child element");
		while (att_element)
		{
			//取id
			int id = att_element->IntAttribute("ID");

			//取属性
			//			tmp_attribute_map = new std::map<std::string,int>();

			std::string sprite = att_element->Attribute("Sprite");
			tmp_attribute_map["Sprite"] = sprite;
			std::string runanimate = att_element->Attribute("Runanimate");
			tmp_attribute_map["Runanimate"] = runanimate;
			std::string dieanimate = att_element->Attribute("Dieanimate");
			tmp_attribute_map["Dieanimate"] = dieanimate;
			//将一条记录加入map
			id_map->insert(std::pair <int,std::map<std::string,std::string> >(id,tmp_attribute_map));

			//取下一个节点
			att_element = att_element->NextSiblingElement();
		}
	}
}



//打开xml
bool ModelAttribute::openXMLFIle(std::string filename){

	if (!FileUtils::getInstance()->isFileExist(filename))
	{
//		log("xml %s open fail!",filename);
		return false;
	}
	xmldocument=new tinyxml2::XMLDocument();
	std::string file=FileUtils::getInstance()->fullPathForFilename(filename);
	log("xml file path:%s",file.c_str());
	long size;
	char *pFileContent = (char*)FileUtils::getInstance()->getFileData(file , "r",&size);
//	log("%s",pFileContent);
	xmldocument->Parse(pFileContent,size);

	log("xml open success!");

	return true;
}

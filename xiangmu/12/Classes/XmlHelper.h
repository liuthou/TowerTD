#ifndef __XMLHELPER_H
#define __XMLHELPER_H
#include <tinyxml2/tinyxml2.h>
#include "cocos2d.h"
#include "platform/apple/CCFileUtilsApple.h"

using namespace tinyxml2;
class XmlHelper
{
protected:
	tinyxml2::XMLDocument xmldoc;
	tinyxml2::XMLElement *root;
	bool isHaveType(std::string type);
	
public:
	std::vector<std::string> types;
	void loadXML(std::string fileName);//载入xml文件
	cocos2d::ValueMap getResoures();//获得资源文件名
	std::string getNextLevel();
	cocos2d::ValueMap getEnemyGroup(int number);//获得enemygroup
	std::vector<cocos2d::ValueMap> getEnenmyGroups();
	std::vector<std::string> getEnemysTypes();
};

void XmlHelper::loadXML(std::string fileName)
{
	auto file = FileUtils::getInstance()->getStringFromFile(fileName);
	xmldoc.Parse(file.c_str());
	//auto file = cocos2d::FileUtils::getInstance()->fullPathForFilename(fileName);
	//xmldoc.LoadFile(file.c_str());
	root = xmldoc.RootElement();
}
cocos2d::ValueMap XmlHelper::getResoures()
{   
	cocos2d::ValueMap valuemap;
	XMLElement *map = root->FirstChildElement("map");
	auto mapname = map->Attribute("name");
	auto mapfile = map->GetText();
	XMLElement *bg = map->NextSiblingElement();
	auto bgname = bg->Attribute("name");
	auto bgfile = bg->GetText();
	XMLElement *money = bg->NextSiblingElement();
	auto moneyName = money->Attribute("name");
	auto moneyNumber = atoi(money->GetText());
	valuemap[mapname] = mapfile;
	valuemap[bgname] = bgfile;
	valuemap[moneyName] = moneyNumber;
	return valuemap;
}
cocos2d::ValueMap XmlHelper::getEnemyGroup(int number)
{   
	cocos2d::ValueMap roundvalue;
	XMLElement *group = root->FirstChildElement("group");
	char str[255];
	sprintf(str,"round%d",number);
	XMLElement *round = group->FirstChildElement(str);
	roundvalue["delytime"] = round->IntAttribute("delytime");
	cocos2d::ValueVector vavc;
	auto roleInfo = FileUtilsApple::getInstance()->getValueMapFromFile("role.npc");
	for (auto it = round->FirstChildElement();it;it = it->NextSiblingElement())
	{      
		  cocos2d::ValueMap valuemap;
          auto id = it->IntAttribute("id");
		  valuemap["id"] = id;
		  std::string type = it->Attribute("type");
		  valuemap["type"] = type;
		  auto enemyinfo = roleInfo.at(type);
		  auto roleName = enemyinfo.asValueMap().at("name").asString();
		  if (!isHaveType(roleName))
		  {
			  types.push_back(roleName);
		  }
		  valuemap["number"] = atoi(it->GetText());
		  valuemap["delytime"] = it->FloatAttribute("delytime");
		  vavc.push_back(cocos2d::Value(valuemap));
	}
	roundvalue["enemyround"] = vavc;
    return roundvalue;
}
std::vector<cocos2d::ValueMap> XmlHelper::getEnenmyGroups()
{   
	std::vector<cocos2d::ValueMap> vc;
	XMLElement *group = root->FirstChildElement("group");
	int i = 1;
	for (auto it = group->FirstChildElement();it;it = it->NextSiblingElement(),i++)
	{
		vc.push_back(getEnemyGroup(i));
	}
	return vc;
}
std::string XmlHelper::getNextLevel()
{   
	std::string next = root->Attribute("nextStage");  //if non attribute shuold judge next whether  is null
	return next;
}                                                    //this we will not use it 
bool XmlHelper::isHaveType(std::string type)
{
	for (auto it = types.begin();it != types.end();it++)
	{
		auto itype = (*it);
		if (itype == type)
		{
			return true;
		}
	}
	return false;
}
std::vector<std::string> XmlHelper::getEnemysTypes()
{
	return types;
}
#endif // !__XMLHELPER_H

#pragma once

#pragma  once

#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"
using namespace cocos2d;
using namespace tinyxml2;




class GetInfoFromXML{
private:
	GetInfoFromXML(const GetInfoFromXML &instance){}
	GetInfoFromXML(){}
	GetInfoFromXML operator=(const GetInfoFromXML &instance){return instance;}
public:

	static GetInfoFromXML *getinstance();
	static GetInfoFromXML *instance;

	void loadXML();
	XMLElement *Stage;
	std::string ID;

	//===================================================地图的信息===============================================
	//获取 地图名字
	CC_SYNTHESIZE(std::string,mapName,MapName);
	//每个获取钢板位置信息
	//CC_SYNTHESIZE(Vec2,bordPos,BordPosition);
	Vec2  bordPos;
	//存放钢板的集合,并返回
	std::vector<Vec2> bordsVector;
	
	std::vector<Vec2> getBordVector();


	//获取钢板的宽
	float mapWidth;
	std::vector<float> allWidth;
	std::vector<float> getAllWidth();
	

	void reloadXML();
	//删除
	void clean();

	
};

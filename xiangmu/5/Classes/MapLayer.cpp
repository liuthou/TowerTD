#include "MapLayer.h"
#include "DynamicBlock.h"
#include "BaseTools.h"
#include "DataXML.h"

MapLayer * MapLayer::create(int mapNum){

	MapLayer * mapLayer = new MapLayer();

	if (mapLayer && mapLayer->init(mapNum))
	{
		mapLayer->autorelease();
		return mapLayer;
	}

	CC_SAFE_DELETE(mapLayer);
	return nullptr;
}

bool MapLayer::init(int mapNum){
	if (!Layer::init())
	{
		return false;
	}
	//加载地图  Loading TileMap
	std::string mapName = StringUtils::format("chickmap%02d.tmx",mapNum);
	tiledMap = TMXTiledMap::create(mapName);
	this->addChild(tiledMap);
	addObject("blocksLayer", 1);
	addObject("toolsLayer", 2);

	return true;
}

void MapLayer::addObject(std::string layerName, int layerType){
	//获取对象层  Get ObjectLayer
	auto objectLayer = tiledMap->getObjectGroup(layerName);
	//获取层上的对象 Get Object in the ObjectLayer
	auto objects = objectLayer->getObjects();
	for (auto object : objects)
	{
		std::string name = object.asValueMap().at("filename").asString();
		float x = object.asValueMap().at("x").asFloat();
		float y = object.asValueMap().at("y").asFloat();
		std::string m_name = object.asValueMap().at("name").asString();
		if (layerType == 1)
		{
			float attack = object.asValueMap().at("attack").asFloat();
			if (object.asValueMap().at("type").asBool()){
				int picNumber = object.asValueMap().at("picnumber").asInt();
				auto dynamicBlock = DynamicBlock::create(name, picNumber, attack, 0.07f, -1, m_name, Vec2(x, y));
				dynamicBlock->setPosition(x, y);
				dynamicBlock->setScale(0.7f);
				this->addChild(dynamicBlock);
			}else{
				auto block = BaseBlock::create(name, attack, m_name, Vec2(x, y));
				block->setPosition(x, y);
				block->setScale(0.7f);
				this->addChild(block);
			}
		}else
		{
			if (DataXML::getInstence()->getInitialValue(m_name) == 1)
			{
				auto state = object.asValueMap().at("state").asInt();
				auto tool = BaseTools::create(name, state, m_name);
				tool->setPosition(x, y);
				tool->setScale(0.7f);
				this->addChild(tool);
			}
		}
	}
}
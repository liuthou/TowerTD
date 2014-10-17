#include "FileManager.h"
#include "HealthData.h"
#include "MainScene.h"
#include "EntityManager.h"
USING_NS_CC;
bool FileManager::init(){
	if (!Node::init())
	{
		return false;
	}
	fileneed=20;
	filereceived=0;
	this->schedule(schedule_selector(FileManager::createFile),5);
	return true;
}

void FileManager::createFile(float dt){
	//以后再改
	auto tmp_data = HealthData::create("tower.png",1000,200);
	MainScene *mScene = dynamic_cast<MainScene *>(Director::getInstance()->getRunningScene());
	auto mapLayer = mScene->getMapLayer();
	auto map = mapLayer->getTiledMap();
	tmp_data->setPosition(monsterCreatePosition());//从地图上拿怪物出生位置
	mapLayer->addChild(tmp_data);
	EntityManager::getInstance()->healthData.pushBack(tmp_data);
}

Vec2 FileManager::monsterCreatePosition(){

	MainScene *mScene = dynamic_cast<MainScene *>(Director::getInstance()->getRunningScene());
	MapLayer *mapLayer = mScene->getMapLayer();
	std::vector<Vec2> burnpoints = mapLayer->enemyBurnPosition();
	int pointsnum = burnpoints.size();
	int i = CCRANDOM_0_1()*pointsnum;
	Vec2 burnp = burnpoints.at(i);
	return burnp;
}
#include "GameScene.h"
#include "backgroundlayer.h"
#include "MainplanLayer.h"
#include "Enemylayer.h"
#include "Score.h"
bool GameScene::init()
{
	if(!Scene::init())
	{
		return false;
	}
	//加载素材,通过文件加载帧缓存。随用随拿
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Resources.plist");
	// 把background层加入到场景中去。
	this->addChild(backgroundlayer::create(),0);
	//2.加入敌机层
	auto EnemyLayer = Enemylayer::create();
	this->addChild(EnemyLayer,1);
	EnemyLayer->setName("Enemylayer");
	//3.加入主机层 设置主机层的名字
	//this->addChild(MainplanLayer::create(),3);//zoder 设置为3
	auto Mainplanlayer =MainplanLayer::create();
	this->addChild(Mainplanlayer,3);
	Mainplanlayer->setName("MainPlaneLayer");
	this->addChild(Score::create());
	return true;
}
Layer * GameScene::getPlantLayer(){
	return this->getChildByName<Layer*>("MainPlaneLayer");
}
Layer* GameScene::getEnemyLayer(){
	return this->getChildByName<Layer*>("Enemylayer");
}
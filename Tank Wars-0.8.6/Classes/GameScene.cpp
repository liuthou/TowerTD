#include "GameScene.h"
#include "MapLayer.h"
#include "Tanklayer.h"
#include "EnemyLayer.h"
#include "LogicLayer.h"
#include "MessageLayer.h"
#include "SimpleAudioEngine.h"
#include "ControlLayer.h"
using namespace CocosDenshion;
bool GameScene::init(){
	if(!Scene::init()){
		return false;
	}
	//加个背景呗
	auto bg = Sprite::create("background.jpg");
	this->addChild(bg, -2);
	bg->setNormalizedPosition(Vec2(0.5, 0.5));

	//加入帧缓存图片
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image.plist");
	SimpleAudioEngine::getInstance()->playEffect("02 start.aif");
	//加入地图层
	auto maplayer = MapLayer::create();
	maplayer->setName("map");
	this->addChild(maplayer);
	//加入主坦克层
	auto tanklyer = Tanklayer::create();
	tanklyer->setName("tanklyer");
	this->addChild(tanklyer);
	//加入敌方坦克
	auto enemylayer = EnemyLayer::create();
	enemylayer->setName("enemlayer");
	this->addChild(enemylayer);
	
	//加入逻辑层
    auto logiclayer = LogicLayer::create();
	this->addChild(logiclayer);
	//加入消息层
	auto messagelayer = MessageLayer::create();
	this->addChild(messagelayer);
	//加入控制层
	auto controllayer = ControlLayer::create();
	controllayer->bindControlTarget((BaseTank *)tanklyer->getChildByName("tank"));
	this->addChild(controllayer);
	return true;
}
Layer* GameScene::getTanklayer(){
	return this-> getChildByName<Layer*>("tanklyer");	
}
Layer* GameScene::getMaplayer(){
	return this-> getChildByName<Layer*>("map");
}
Layer* GameScene::getenemlayer(){
	return this-> getChildByName<Layer*>("enemlayer");	
}
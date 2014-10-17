#include "GameScene.h"
#include "ControlLayer.h"
#include "BackgroundLayer.h"
#include "ShowLayer.h"
#include "taskLayer.h"
#include "DataXML.h"
#include "BoundingLayer.h"
#include "GameData.h"
#include "RoleLayer.h"

bool GameScene::init(){
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	this->setName("game_scene");

	//添加背景层：各种远景/障碍
	auto backgroundLayer = BackgroundLayer::create();
	backgroundLayer->setName("BackLayer");
	this->addChild(backgroundLayer);

	//添加主角层
	auto roleLayer = RoleLayer::create();
	roleLayer->setName("RoleLayer");
	this->addChild(roleLayer);

	//添加控制层：控制
	auto controlLayer = ControlLayer::create();
	controlLayer->setName("ControlLayer");
	this->addChild(controlLayer);

	//添加显示层：显示框，分数，血条，条件等
	auto showLayer = ShowLayer::create();
	this->addChild(showLayer);

	//添加碰撞层
	auto boundingLayer = BoundingLayer::create();
	this->addChild(boundingLayer);
	

	return true;
}

void GameScene::onEnter() {

	Scene::onEnter();
	audioFlag = DataXML::getInstence()->getInitialValue("sound");
	BACK_GUOUND_MUSIC("chickendance.mp3",audioFlag);
}

Layer * GameScene::getRoleLayer(){
	return dynamic_cast<Layer *>(this->getChildByName("RoleLayer"));
}

Layer * GameScene::getControlLayer(){
	return dynamic_cast<Layer *>(this->getChildByName("ControlLayer"));
}

Layer * GameScene::getBackgroundLayer(){
	return dynamic_cast<Layer *>(this->getChildByName("BackLayer"));
}
#include "MainScene.h"
#include"GameLayer.h"
#include"Enemy.h"
#include "NormalTower.h"
#include "EntityManager.h"
#include "ForwardLayer.h"
#include "VictorySprite.h"
#include "InjuredEffent.h"
#include "MapLayer.h"
bool GameLayer::init(){
	if (!Layer::init())return false;

	//auto tow = NormalTower::create("card_1.png");
	//tow->setPosition(300,300);
	//tow->fire(Vec2(200,300));
	return true;
}
void GameLayer::onEnter(){
	Layer::onEnter();
	//auto en = Entity::create("long.png",100,200,80);
	//Vec2 pos = Director::getInstance()->getVisibleSize();
	//en ->setPosition(pos.x/2,pos.y/2);
	//en->setZOrder(10);
	//auto tow = NormalTower::create("card_1.png");
	//tow->setZOrder(10);
	//tow->setPosition(300,300);
	//tow->fire(Vec2(100,200));
	auto scene = Director::getInstance()->getRunningScene();
	MapLayer* map = dynamic_cast<MapLayer*>(scene->getChildByTag(100));
	//胜利精灵
	auto sp = VirctoSprite::create(100,25);
	//测试测试测试
	sp->setPosition(map->MonstEndPosition());
	sp->setContentSize(Size(640,10));
	this->addChild(sp);
	//测试测试测试
	//绑定受伤效果函数
	auto injuredlayer = dynamic_cast<InjuredEffect*>(scene->getChildByName("injuredEffect"));
	sp->setHurtEffectFunc(CC_CALLBACK_2(InjuredEffect::beInjured,injuredlayer));
	//绑定更新进度条函数
	auto progresslayer = dynamic_cast<ForwardLayer*>(scene->getChildByName("progressLayer"));
	sp->setProgressFunc(CC_CALLBACK_1(ForwardLayer::loadingCallBack,progresslayer));
	//绑定失败函数
	auto currentscene = dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
	sp->setLoseFunc(CC_CALLBACK_0(MainScene::lose,currentscene));
	//绑定胜利函数
	sp->setWinFunc(CC_CALLBACK_0(MainScene::win,currentscene));
	this->scheduleUpdate();
}
void GameLayer::onExit(){
	Layer::onExit();
}

void GameLayer::update(float dt){
	int count = this->getChildrenCount();
	EntityManager::getInstance()->checkBulletHitMonster();
	EntityManager::getInstance()->checkBulletHitTower();
	EntityManager::getInstance()->removeInvalidTowerEnemy();
}

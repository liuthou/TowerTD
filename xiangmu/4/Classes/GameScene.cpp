#include "GameScene.h"
#include "HeroesLayer.h"
#include "CollideLayer.h"
#include "ScoreLayer.h"
class CollideLayer;
#include "BackgroundLayer.h"
bool GameScene::init()
{
   if (!Scene::init())
   {
	   return false;
   }
   return true;
}

void GameScene::onEnter(){
	Scene::onEnter();
	//创建背景层
	auto bgLayer = BackgroundLayer::create();
	this->addChild(bgLayer,0);

	//创建主机层
	auto herolayer = HeroesLayer::create("HeroFly1.png");
	herolayer->setName("HeroLayer");
	this->addChild(herolayer);

	//创建敌机层
	auto enemyLayer = EnemyLayer::create();
	enemyLayer->setName("EnemyLayer");
	this->addChild(enemyLayer);

	//创建碰撞层
	auto colideLayer = CollideLayer::create();
	colideLayer->setName("ColideLayer");
	this->addChild(colideLayer);

	auto score = ScoreLayer::create();
	score->setName("Score");
	this->addChild(score);
}

//获取主机层
HeroesLayer * GameScene::getHeroLayer()
{
	auto hr = dynamic_cast<HeroesLayer *>(this->getChildByName("HeroLayer"));
	return hr;
}

//获取敌机层
EnemyLayer* GameScene::getEnemyLayer(){
	return (EnemyLayer *)this->getChildByName("EnemyLayer");
}

//获取碰撞层
Layer* GameScene::getColideLayer(){
	return (Layer *)this->getChildByName("ColideLayer");
}

ScoreLayer *GameScene::getScoreLayer(){
	return (ScoreLayer *)this->getChildByName("Score");
}
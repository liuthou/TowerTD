#include "testLayer.h"
#include "StageLayer.h"
#include "GameManager.h"
#include "Enemy.h"
#include "MapLayer.h"
#include "BigArrow.h"
#include "YellowThunder.h"
#include "TowerOne.h"
#include "IceSkill.h"
#include "BoneSkill.h"
#include "WindSkill.h"
#include "EnemyLayer.h"
#include "FireSkill.h"
Layer* testLayer::shareTowerLayer = nullptr;
bool testLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SkillThunders.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("otherskill.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hurt.plist");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("NewAnimation/NewAnimation.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo( "Project Animation/Project Animation.ExportJson");	
	//gamemanger and xmlhelper test
	/*auto stagelayer = StageLayer::create();
	this->addChild(stagelayer);
	shareTowerLayer = stagelayer;*/
	auto enemyLayer = Enemylayer::create();
//	stagelayer->addChild(enemyLayer);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch *t,Event *e){
		/*auto thunderskill = YellowThunder::create(t->getLocation());
		this->addChild(thunderskill);*/
		/*auto baseskill = FireSkill::create(t->getLocation(),Vec2(1200,100));
		this->addChild(baseskill);*/
		/*auto tower = TowerOne::create("");
		tower->setPosition(t->getLocation());
		this->addChild(tower);*/
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	return true;
}

void testLayer::addEnemy(float t)
{
	/*auto baseskill2 = BigArrow::create(Vec2(100,200),Vec2(200,500));
	this->addChild(baseskill2);*/
	/*auto baseskill = FireSkill::create(Vec2(100,200),Vec2(1200,500));
	this->addChild(baseskill);*/
}

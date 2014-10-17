#include "GameMainScene.h"
#include "HeroMacro.h"
#include "MonsterLayer.h"
#include "HaemalStrandLayer.h"
#include "ExperienceLayer.h"
#include "HeroLayer.h"
#include "BackgroundLayer.h"
#include "StartScene.h"
#include "MonsterSoldier.h"
#include "SkillShowLayer.h"
#include "T_GameMainScene.h"
#include "CollideManage.h"
#include "SundriesLayer.h"
#include "GameFinishLayer.h"
#include "BackLayer.h"
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;

GameMainScene *GameMainScene::create(std::string filename){
	auto scene = new GameMainScene();
	if (scene&&scene->init(filename)){
		scene->autorelease();
		return scene;
	}
	else
	{
		CC_SAFE_DELETE(scene);
		return nullptr;
	}
}
bool GameMainScene::init(std::string filename)
{
	if(!Scene::init())
	{
	    return false;
	}
//	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(HERO_PICTURE_PLIST);	
//	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(SWORD_SKILL_PLIST);
//	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(SHAN_DIAN_PLIST);
//	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(MONSTER_GEBULIN_PLIST);
//	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(MONSTER_NANGUA_PLIST);
//	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(MONSTER_BOOS_PLIST);
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bigSkill.plist");
//	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bigSkillButton.plist");
	//技能显示层
	SkillShowLayer * skillShowLayer = SkillShowLayer::create();
	this->addChild(skillShowLayer);
	//怪物层
	MonsterLayer *monsterlayer = MonsterLayer::create(filename);
	this->addChild(monsterlayer);
	monsterlayer->setName("monsterlayer");
	//主角层
	HeroLayer *heroLayer = HeroLayer::create();
	heroLayer->setName("heroLayer");
	this->addChild(heroLayer);
	//背景层
	this->addChild(BackgroundLayer::create(filename), -1);
	auto button = MenuItemImage::create("button1.png", "button2.png", [=](Ref * sender){
		auto back = BackLayer::create();
		this->addChild(back);
        SimpleAudioEngine::getInstance()->playEffect("ItemPress.wav");
		Director::getInstance()->pause();
	});
    Size s = Director::getInstance()->getVisibleSize();
    Sprite *pSprite = Sprite::create("button1.png");
    Size ps = pSprite->getContentSize();
    button->setPosition(Vec2(s.width-ps.width,s.height-ps.height));
	auto menu = Menu::create(button, NULL);
	menu->setPosition(Vec2::ZERO);

	this->addChild(menu,100);
	//经验条层
	ExperienceLayer * experienceLayer = ExperienceLayer::create();
	this->addChild(experienceLayer);
    //人物血条和蓝条
    HaemalStrandLayer * haemalStrandLayer = HaemalStrandLayer::create();
	this->addChild(haemalStrandLayer);
	//杂物层
	SundriesLayer * sundriesLayer = SundriesLayer::create();
	sundriesLayer->setName("sundriesLayer");
	this->addChild(sundriesLayer);
	//管理层
	CollideManage * collideManage = CollideManage::create();
	this->addChild(collideManage);
	//设置监听，观察boos是否死亡
	auto boosDie = __NotificationCenter::getInstance();
	boosDie->addObserver(this, callfuncO_selector(GameMainScene::addWinLayer),"BoosDie",nullptr);
    SimpleAudioEngine::getInstance()->playBackgroundMusic("Att04.wav", true);
	return true;
}

Layer *GameMainScene::getMonsterLayer()
{
	return this->getChildByName<Layer *>("monsterlayer");
}

Layer *GameMainScene::getHeroLayer()
{
	return this->getChildByName<Layer *>("heroLayer");
}

Layer *GameMainScene::getSundriesLayer()
{
	return this->getChildByName<Layer *>("sundriesLayer");
}

void GameMainScene::addWinLayer(Ref * obj)
{
	this->runAction(Sequence::create(DelayTime::create(2), CallFunc::create([=](){
		GameFinishLayer * gameWin = GameFinishLayer::create();
		this->addChild(gameWin);
	}), nullptr));
}

GameMainScene::~GameMainScene()
{
	auto boosDie = __NotificationCenter::getInstance();
	boosDie->removeObserver(this, "BoosDie");
}
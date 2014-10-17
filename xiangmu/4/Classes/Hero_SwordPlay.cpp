#include "Hero_SwordPlay.h"
#include "PetWolf.h"
#include "GameScene.h"
#include "GameOverLayer.h"

Hero_SwordPlay * Hero_SwordPlay::create()
{
	Hero_SwordPlay * hero_SwordPlay = new Hero_SwordPlay();
	if (hero_SwordPlay && hero_SwordPlay->init())
	{
		hero_SwordPlay->autorelease();
		return hero_SwordPlay;
	}
	CC_SAFE_DELETE(hero_SwordPlay);
	return nullptr;
}

bool Hero_SwordPlay::init()
{
	if (!BaseHeroes::initWithSpriteFrameName("HeroFly1.png"))
	{
		return false;
	}
    return true;
}

void Hero_SwordPlay::die()
{
	this->stopAllActions();
	this->unschedule(schedule_selector(Hero_SwordPlay::addFire));
	auto dieAni = ShareFunc::getAct("HeroDie1.png", 1, 11, 0.2, 1);
	auto scene = (GameScene *)Director::getInstance()->getRunningScene();
	auto heroLayer = scene->getHeroLayer();
	heroLayer->setTouchesStop(true);
	heroLayer->setHeroDie();
	auto cbStop = CallFunc::create([=](){
		//		heroLayer->stopAllActions();
		Director::getInstance()->pause();

		auto gameOverLayer = GameOverLayer::create();
		scene->addChild(gameOverLayer, 6);
	});
	this->runAction(Sequence::create(dieAni,cbStop,NULL));
	auto pet = (PetWolf *)heroLayer->getChildByName("pet");
	pet->die();
}
//受伤动画
ActionInterval * Hero_SwordPlay::hurtAnimate()
{
	return ShareFunc::getAct("Herohurt1.png",1,1,1,1);
}

//飞行动画
ActionInterval * Hero_SwordPlay::flyAnimate()
{
	return ShareFunc::getAct("HeroFly1.png",1,4,0.2,-1);
}


void Hero_SwordPlay::onEnter()
{
	BaseHeroes::onEnter();
	this->fly();
}

void Hero_SwordPlay::fly()
{
	aniFly = flyAnimate();
	//aniFly->retain();
	this->runAction(aniFly);
}

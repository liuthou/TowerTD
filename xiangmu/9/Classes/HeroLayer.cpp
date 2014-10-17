#include "HeroLayer.h"
#include "SwordmanHero.h"

bool HeroLayer::init()
{
	if(!Layer::init())
	{
	     return false;
	}
	//获得可视屏幕的大小
	Vec2 vSize = Director::getInstance()->getVisibleSize();
	//导入英雄
	SwordmanHero * hero = SwordmanHero::create();
	hero->setTag(100);
	this->addChild(hero);
	return true;
}



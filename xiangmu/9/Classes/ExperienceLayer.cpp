#include "ExperienceLayer.h"
#include "DataCacheHero.h"
#include "HeroBase.h"

bool ExperienceLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	DataCacheHero * dataCacheHero = DataCacheHero::getInstance();
	Sprite * experGround = Sprite::create("jingyan_ground.png");
	experGround->setPosition(480, 10);
	experGround->setScale(2.91, 1.49);
	this->addChild(experGround);
	_heroExperience = Sprite::create("jingyan_jindu.png");
	//经验条
	_fillExperience = ProgressTimer::create(_heroExperience);
	_fillExperience->setScale(2.91,1.79);
    _fillExperience->setPosition(497,19);
	this->setFill(_fillExperience);
	this->addChild(_fillExperience,1);
	_fillExperience->setType(ProgressTimer::Type::BAR);
	_fillExperience->setMidpoint(Point(0, 0.5));
	_fillExperience->setBarChangeRate( Point(1.0, 0));
	int expHero = 100 * (1 - (float)(dataCacheHero->getExpValue()) - (dataCacheHero->getNowExpValue()) / (float)(dataCacheHero->getNeedExpValue()));
	_fillExperience->setPercentage(expHero);
	//猪脚增加经验
	auto heroAddExp = __NotificationCenter::getInstance();
	heroAddExp->addObserver(this, callfuncO_selector(ExperienceLayer::heroChangeExp), "heroAddExp", nullptr);
	return true;
}

void ExperienceLayer::heroChangeExp(Ref * obj)
{
	HeroBase * heroBase = dynamic_cast<HeroBase *>(obj);
	int heroExp = 100 * (1 - ((float)(heroBase->getExpValue() - heroBase->getNowExpValue()) /(float) heroBase->getNeedExpValue()));
	_fillExperience->setPercentage(heroExp);
}

ExperienceLayer::~ExperienceLayer()
{
	auto heroAddExp = __NotificationCenter::getInstance();
	heroAddExp->removeObserver(this,"heroAddExp");
}



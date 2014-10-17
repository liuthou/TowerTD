#include "HaemalStrandLayer.h"
#include "HeroBase.h"

bool HaemalStrandLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	_hpMpGround = Sprite::create(HPMPGROUND);
	_hpMpGround->setPosition(HPMPGROUND_POINT);
	this->addChild(_hpMpGround,4);
	_heroHpStrip = Sprite::create(HEROHPPICTURE);
	_heroMpStrip = Sprite::create(HEROMPPICTURE);
	//ÑªÌõ
	_fillHp = ProgressTimer::create(_heroHpStrip);
	_fillHp->setScale(HP_SCALE);
    _fillHp->setPosition(HP_POINT);
	this->setFill(_fillHp);
	this->addChild(_fillHp,1);
	_fillHp->setType(ProgressTimer::Type::BAR);
	_fillHp->setMidpoint(HP_MIDPOINT);
	_fillHp->setBarChangeRate(HP_BARCHANGERATE);
	_fillHp->setPercentage(100);
	//Ä§·¨ÖµÌõ
	_fillBule = ProgressTimer::create(_heroMpStrip);
	_fillBule->setScale(MP_SCALE);
	_fillBule->setPosition(MP_POINT);
	this->setFill(_fillBule);
	this->addChild(_fillBule,1);
	_fillBule->setType(ProgressTimer::Type::BAR);
	_fillBule->setMidpoint(MP_MIDPOINT);
	_fillBule->setBarChangeRate(MP_BARCHANGERATE);
	_fillBule->setPercentage(100);
	//×¢²áÊÜ¹¥»÷Í¨Öª
	auto censerhp = __NotificationCenter::getInstance();
	censerhp->addObserver(this, callfuncO_selector(HaemalStrandLayer::heroHurtHp), "heroHurtHp", nullptr);
	//×¢²áºÄÀ¶Í¨Öª
	auto censermp = __NotificationCenter::getInstance();
	censermp->addObserver(this, callfuncO_selector(HaemalStrandLayer::heroCostLan), "heroCostlan", nullptr);
	return true;
}

void HaemalStrandLayer::heroHurtHp(Ref *f)
{
	HeroBase * heroBase = dynamic_cast<HeroBase *>(f);
	int hpRate =100 * ((float)heroBase->getHpValue()/heroBase->getAllHp());
	_fillHp->setPercentage(hpRate);
}

void HaemalStrandLayer::heroCostLan(Ref *f)
{
	HeroBase * heroBase = dynamic_cast<HeroBase *>(f);
	int mpRate =100 * ((float)heroBase->getMpValue()/heroBase->getAllMp());
	_fillBule->setPercentage(mpRate);
}

HaemalStrandLayer::~HaemalStrandLayer()
{
	//É¾³ý×¢²áÊÜ¹¥»÷Í¨Öª
	auto censerhp = __NotificationCenter::getInstance();
	censerhp->removeObserver(this, "heroHurtHp");
	//É¾³ý×¢²áºÄÀ¶Í¨Öª
	auto censermp = __NotificationCenter::getInstance();
	censermp->removeObserver(this, "heroCostlan");      
}
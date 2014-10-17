#include "SwordAnger.h"
#include "AnimateClass.h"
#include "Skilles.h"
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;
SwordAnger * SwordAnger::create(Vec2 skillPoint,  int dir)
{
	SwordAnger * swordAnger = new SwordAnger();
	if(swordAnger && swordAnger->init(skillPoint, dir))
	{
		swordAnger->autorelease();
		return swordAnger;
	}
	CC_SAFE_DELETE(swordAnger);
	return NULL;
}

bool SwordAnger::init(Vec2 skillPoint, int dir)
{
	if(!SkillBase::init("sword_skill0.png",skillPoint))
	{
	    return false;
	}
    this->setOpacity(200);
	//读取技能数据容器
	Skilles * skilles = Skilles::getInstance();
	_attack = (* skilles->getSkilles().begin())->getAttickValue();
	//魔法消耗值
	_consumeMp = (* skilles->getSkilles().begin())->getConsumeMp();
	//dir技能释放的方向
	skillAntimate(dir);
    return true;
}

void SwordAnger::skillAntimate(int dir)
{
    SimpleAudioEngine::getInstance()->playEffect("skillOne.wav");
	AnimateClass * skillAnimate = AnimateClass::create();
	if(dir == LEFTFARSKILL1)
	{
		this->setRotationY(180);
	    this->runAction(Sequence::create( Spawn::create(MoveBy::create(1.3,Vec2(-500,0)),skillAnimate->skillSwordAnger(),NULL),CallFunc::create(CC_CALLBACK_0(SwordAnger::removeAntimate,this)),NULL));
	}
	if(dir == RIGHTFARSKILL1)
	{
		this->setRotationY(0);
	    this->runAction(Sequence::create( Spawn::create(MoveBy::create(1.3,Vec2(500,0)),skillAnimate->skillSwordAnger(),NULL),CallFunc::create(CC_CALLBACK_0(SwordAnger::removeAntimate,this)),NULL));
	}
}

void SwordAnger::removeAntimate()
{
	this->removeFromParent();
	_isDie = true;
}
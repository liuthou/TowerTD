#include "ArrowSkill.h"


ArrowSkill * ArrowSkill::create(Vec2 curpoint ,Vec2 movepoint)
{
	auto pef = new ArrowSkill();
	if (pef&&pef->init(curpoint,movepoint))
	{
		pef->autorelease();
		return pef;
	}
	CC_SAFE_DELETE(pef);
	return nullptr;
}
bool ArrowSkill::init(Vec2 &curpoint ,Vec2 &movepoint)
{     
	if (!BaseSkill::init("arrow_01.png", curpoint , movepoint))
	{
		return false;
	}
	this->state = 0;
	this->attack = ARROWATK;
	SimpleAudioEngine::getInstance()->playEffect("OM_ATK.mp3");
	return true;
}
Animate * ArrowSkill::dieAnimate()
{     
	auto animation = Animation::create();
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("arrow_01.png");
	animation->addSpriteFrame(spriteFrame);
	spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("arrow_02.png");
	animation->addSpriteFrame(spriteFrame);
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(1);
	auto animate = Animate::create(animation);
	return animate;
}
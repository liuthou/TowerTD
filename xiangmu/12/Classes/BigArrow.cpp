#include "BigArrow.h"
#include "GameBasic.h"

BigArrow * BigArrow::create(Vec2 curpoint ,Vec2 movepoint)
{
	auto pef = new BigArrow();
	if (pef&&pef->init(curpoint,movepoint))
	{
		pef->autorelease();
		return pef;
	}
	CC_SAFE_DELETE(pef);
	return nullptr;
}
bool BigArrow::init(Vec2 &curpoint ,Vec2 &movepoint)
{     
	if (!ArrowSkill::init(curpoint,movepoint))
	{
		return false;
	}
	Sprite::initWithSpriteFrameName("bigarrow_01.png");
	this->attack = BIGARROWATK;
	return true;
}
Animate * BigArrow::dieAnimate()
{
	auto animation = Animation::create();
	auto spriteframe = SpriteFrameCache::getInstance()->getSpriteFrameByName("bigarrow_01.png");
	animation->addSpriteFrame(spriteframe);
	spriteframe = SpriteFrameCache::getInstance()->getSpriteFrameByName("bigarrow_02.png");
	animation->addSpriteFrame(spriteframe);
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(1);
	auto animate = Animate::create(animation);
	return animate;
}
#include "FireSkill.h"
FireSkill * FireSkill::create(Vec2 curpoint ,Vec2 movepoint)
{
	auto pef = new FireSkill();
	if (pef&&pef->init(curpoint,movepoint))
	{
		pef->autorelease();
		return pef;
	}
	CC_SAFE_DELETE(pef);
	return nullptr;
}
bool FireSkill::init(Vec2 &curpoint ,Vec2 &movepoint)
{     
	if (!BaseSkill::init("fire_01.png", curpoint , movepoint))
	{
		return false;
	}
	this->state = 1;
	this->attack = FIRESKILL;
	this->setScale(2);
	SimpleAudioEngine::getInstance()->playEffect("abstacleDestroy.wav");
	return true;
}

Animate * FireSkill::dieAnimate()
{  
	Vector<SpriteFrame *> vector;
	for (int i = 1;i < 9;i++)
	{   auto str = StringUtils::format("fire_%02d.png",i);
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
	vector.pushBack(spriteFrame);
	}
	auto animation = Animation::createWithSpriteFrames(vector,0.1f,1);
	auto animate = Animate::create(animation);
	return animate;
}
void FireSkill::skillRotateAnimate(float t)
{

}
#include "DoubleThunder.h"

DoubleThunder *DoubleThunder::create(Vec2 curpoint)
{   
	auto pef = new DoubleThunder();
	if (pef&&pef->init(curpoint))
	{
		pef->autorelease();
		return pef;
	}
	CC_SAFE_DELETE(pef);
	return nullptr;
}
bool DoubleThunder::init(Vec2 &curpoint)
{   
	std::string filename = "thunder2_01.png";
	if (!ThunderSkill::init(curpoint))
	{   
		return false;
	}
	Sprite::initWithSpriteFrameName(filename);
	this->attack = DOUBLETHUNDER;//set this skill property
	return true;
}
void DoubleThunder::attackAnimate() //exec attack animation
{
	Vector<SpriteFrame *> vector;
	for (int i = 1;i < 18;i++)
	{
		std::string str = StringUtils::format("thunder2_%02d.png",i);
		auto spfame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		vector.pushBack(spfame);
	}
	auto animation = Animation::createWithSpriteFrames(vector,0.2,-1);
	auto animate = Animate::create(animation);
	this->runAction(animate);
}
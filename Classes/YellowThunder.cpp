#include "YellowThunder.h"

YellowThunder *YellowThunder::create(Vec2 curpoint)
{   
	auto pef = new YellowThunder();
	if (pef&&pef->init(curpoint))
	{
		pef->autorelease();
		return pef;
	}
	CC_SAFE_DELETE(pef);
	return nullptr;
}
bool YellowThunder::init(Vec2 &curpoint)
{   
	std::string filename = "thunder3_01.png";
	if (!ThunderSkill::init(curpoint))
	{ 
		return false;
	}
	Sprite::initWithSpriteFrameName(filename);
	this->state = 4;
	this->attack = YELLOWTHUNDER;//set this skill property	
	return true;
}
void YellowThunder::attackAnimate() //exec attack animation
{
	Vector<SpriteFrame *> vector;
	for (int i = 1;i < 7;i++)
	{
		std::string str = StringUtils::format("thunder3_%02d.png",i);
		auto spfame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		vector.pushBack(spfame);
	}
	auto animation = Animation::createWithSpriteFrames(vector,0.2,-1);
	auto animate = Animate::create(animation);
	this->runAction(animate);
}

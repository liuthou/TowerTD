#include "WindSkill.h"

WindSkill *WindSkill::create(Vec2 curpoint)
{   
	auto pef = new WindSkill();
	if (pef&&pef->init(curpoint))
	{
		pef->autorelease();
		return pef;
	}
	CC_SAFE_DELETE(pef);
	return nullptr;
}
bool WindSkill::init(Vec2 &curpoint)
{   
	std::string filename = "wind_01.png";
	if (!ThunderSkill::init(curpoint))
	{   
		return false;
	}
	Sprite::initWithSpriteFrameName(filename);
	this->setDuration(3);
	this->attack = WINDSKILL;
	this->state = 3; //set this skill property
	SimpleAudioEngine::getInstance()->playEffect("Music/wind.mp3");
	return true;
}
void WindSkill::attackAnimate() //exec attack animation
{
	Vector<SpriteFrame *> vector;
	for (int i = 3;i < 5;i++)
	{
		std::string str = StringUtils::format("wind_%02d.png",i);
		auto spfame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		vector.pushBack(spfame);
	}
	auto animation = Animation::createWithSpriteFrames(vector,0.1f,-1);
	auto animate = Animate::create(animation);
	this->runAction(animate);
}
bool WindSkill::boundHurt()
{return false;}

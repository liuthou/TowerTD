#include "ThunderSkill.h"
#include "Enemy.h"
ThunderSkill *ThunderSkill::create(Vec2 curpoint)
{   
	auto pef = new ThunderSkill();
	if (pef&&pef->init(curpoint))
	{
		pef->autorelease();
		return pef;
	}
	CC_SAFE_DELETE(pef);
	return nullptr;
}
bool ThunderSkill::init(Vec2 &curpoint)
{   
	std::string filename = "thunder1_01.png";
	
	if (!BaseSkill::init(filename,curpoint,curpoint))
	{
		return false;
	}
	this->attack = THUNDERSKILL;
	this->state = 4; //set this skill property
	this->setDuration(2);
	SimpleAudioEngine::getInstance()->playEffect("Music/LINA_ATK3.mp3");
	return true;
}
void ThunderSkill::attackAnimate() //exec attack animation
{
	Vector<SpriteFrame *> vector;
	for (int i = 1;i < 8;i++)
	{
		std::string str = StringUtils::format("thunder1_%02d.png",i);
		auto spfame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		vector.pushBack(spfame);
	}
	auto animation = Animation::createWithSpriteFrames(vector,0.2f,-1);
	auto animate = Animate::create(animation);
	this->runAction(animate);
}
bool ThunderSkill::boundHurt()
{return false;}

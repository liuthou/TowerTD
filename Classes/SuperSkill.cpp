#include "SuperSkill.h"

SuperSkill *SuperSkill::create(Vec2 curpoint,int type)
{   
	auto pef = new SuperSkill();
	if (pef&&pef->init(curpoint,type))
	{
		pef->autorelease();
		return pef;
	}
	CC_SAFE_DELETE(pef);
	return nullptr;
}
bool SuperSkill::init(Vec2 &curpoint,int type)
{   
	std::string fileName = "";
	this->type = type;
	switch (type)
	{
	case SUPERWIND:
		fileName = "wind_0.png";
		break;
	case SUPERTHUNDER:
		fileName = "wire_0.png";
		break;
	case SUPERICE:
		fileName = "ice_0.png";
	    break;
	case SUPERFIRE:
		fileName = "fire_0.png";
		break;
	default:
		break;
	}
	if (!(ThunderSkill::init(curpoint)&&Sprite::initWithSpriteFrameName(fileName)))
	{
		return false;
	}
	
	this->duration = 4.0f;
	this->attack = 3.5;
	this->state = type;
	return true;
}
void SuperSkill::attackAnimate()
{
	auto an = Animation::create();
	switch (this->type)
	{
	case SUPERWIND:
		for(int i=0;i<13;i++){
			auto str =StringUtils::format("wind_%d.png",i);
			auto fram =SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
			an->addSpriteFrame(fram);
		}
		break;
	case SUPERTHUNDER:
		for(int i = 0;i < 15;i++){
			auto str =StringUtils::format("wire_%d.png",i);
			auto fram =SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
			an->addSpriteFrame(fram);
		}
		break;
	case SUPERICE:
		for(int i = 0;i < 15;i++){
			auto str =StringUtils::format("ice_%d.png",i);
			auto fram =SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
			an->addSpriteFrame(fram);
		}
		break;
	case SUPERFIRE:
		for(int i = 0;i < 6;i++){
			auto str =StringUtils::format("fire_%d.png",i);
			auto fram =SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
			an->addSpriteFrame(fram);
		}
		break;
	default:
		break;
	}
	an->setDelayPerUnit(0.2f);
	an->setLoops(-1);
	this->runAction(Animate::create(an));
}
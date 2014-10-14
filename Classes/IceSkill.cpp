#include "IceSkill.h"

IceSkill * IceSkill::create(Vec2 curpoint ,Vec2 movepoint)
{
	auto pef = new IceSkill();
	if (pef&&pef->init(curpoint,movepoint))
	{
		pef->autorelease();
		return pef;
	}
	CC_SAFE_DELETE(pef);
	return nullptr;
}
bool IceSkill::init(Vec2 &curpoint ,Vec2 &movepoint)
{     
	if (!BaseSkill::init("cool_01.png", curpoint , movepoint))
	{
		return false;
	}
	this->state = 2;
	this->attack = ICESKILL;

	return true;
}

void IceSkill::moveAnimate()
{
	float _distance = 0;
	if (!(_distance = m_curpoint.getDistance(m_movepoint)))
	{
		return;
	}
	SimpleAudioEngine::getInstance()->playEffect("Music/attack31.mp3");
	auto _call = CallFunc::create([=](){this->die(0);}); 
	auto _sequ = Sequence::create(MoveTo::create(_distance/500,m_movepoint),_call,NULL);
	this->runAction(_sequ);
}
Animate * IceSkill::dieAnimate()
{  
	Vector<SpriteFrame *> vector;
	for (int i = 1;i < 6;i++)
	{   auto str = StringUtils::format("cool_%02d.png",i);
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		vector.pushBack(spriteFrame);
	}
	auto animation = Animation::createWithSpriteFrames(vector,0.1f,1);
	auto animate = Animate::create(animation);
	return animate;
}


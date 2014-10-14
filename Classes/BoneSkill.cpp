#include "BoneSkill.h"

BoneSkill * BoneSkill::create(Vec2 curpoint ,Vec2 movepoint)
{
	auto pef = new BoneSkill();
	if (pef&&pef->init(curpoint,movepoint))
	{
		pef->autorelease();
		return pef;
	}
	CC_SAFE_DELETE(pef);
	return nullptr;
}
bool BoneSkill::init(Vec2 &curpoint ,Vec2 &movepoint)
{     
	if (!BaseSkill::init("bone_01.png", curpoint , movepoint))
	{
		return false;
	}
	this->attack = BONESKILL;
	SimpleAudioEngine::getInstance()->playEffect("Music/MED_ATK.mp3");
	return true;
}
Animate * BoneSkill::dieAnimate()
{
	Vector<SpriteFrame *> vector;
	for (int i = 1;i < 8;i++)
	{
		std::string str = StringUtils::format("bone_%02d.png",i);
		auto spfame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		vector.pushBack(spfame);
	}
	auto animation = Animation::createWithSpriteFrames(vector,0.1,1);
	auto animate = Animate::create(animation);
	return animate;
}
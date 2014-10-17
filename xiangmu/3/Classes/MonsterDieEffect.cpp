#include "MonsterDieEffect.h"
USING_NS_CC;
MonsterDieEffect* MonsterDieEffect::create(Vec2 appearpoint,Vec2 disappearpoint,std::string effectfile1,std::string effectfile2){
	auto monsterdieeffect = new MonsterDieEffect();
	if (monsterdieeffect&&monsterdieeffect->init(appearpoint,disappearpoint,effectfile1,effectfile2))
	{
		monsterdieeffect->autorelease();
		return monsterdieeffect;
	}
	delete monsterdieeffect;
	monsterdieeffect = nullptr;
	return monsterdieeffect;
}
bool MonsterDieEffect::init(Vec2 appearpoint,Vec2 disappearpoint,std::string effectfile1,std::string effectfile2){
	if (!Sprite::init())
	{
		return false;
	}
	auto particle0 = ParticleSystemQuad::create(effectfile1);
	particle0->setGravity(disappearpoint-appearpoint);
	this->setPosition(appearpoint);
	particle0->setAutoRemoveOnFinish(true);
	this->addChild(particle0);
	auto particle1 = ParticleSystemQuad::create(effectfile2);
	particle1->setGravity(disappearpoint-appearpoint);
	this->setPosition(appearpoint);
	particle1->setAutoRemoveOnFinish(true);
	this->addChild(particle1);


	//做完特效移除自己
	this->scheduleOnce(schedule_selector(MonsterDieEffect::autoRemoveSelf),2);
	return true;
}

void MonsterDieEffect::autoRemoveSelf(float dt){
	this->removeAllChildren();
	this->removeFromParent();
}
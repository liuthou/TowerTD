#include "T_SkillShowLayer.h"
#include "SkillShowLayer.h"
#include "HeroBase.h"
#include "HeroMacro.h"

Scene * SkillShowLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = SkillShowLayer::create();
	scene->addChild(layer);
	return scene;
}

bool SkillShowLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	_skill1 = Sprite::create(SKILLONE);
	_skill1->setPosition(SKILL1_POINT);
	_skill2 = Sprite::create(SKILLTWO);
	_skill2->setPosition(SKILL2_POINT);
	_skill3 = Sprite::create(SKILLTHREE);
	_skill3->setPosition(SKILL3_POINT);
	this->addChild(_skill3);
	this->addChild(_skill2);
	this->addChild(_skill1);
	skill3Progress();
	//添加观察者
	auto centerSkill = __NotificationCenter::getInstance();
	centerSkill->addObserver(this,callfuncO_selector(SkillShowLayer::skillObserver), "SkillType", nullptr);
	//添加观察者
	auto bigskillend = __NotificationCenter::getInstance();
	centerSkill->addObserver(this,callfuncO_selector(SkillShowLayer::skill3), "BigSkillEnd", nullptr);
	return true;
}

void SkillShowLayer::skillObserver(Ref * obj)
{
	auto heroBase = static_cast<HeroBase*>(obj);
	_skillType = heroBase->getDIR();
	if (_skillType == LEFTFARSKILL || _skillType == RIGHTFARSKILL) 
	{
		skill1Progress(_skill1,SKILLONE, SKILL1_CD_TIME, 1);
	}else if (_skillType == NEARSKILL)
	{
		skill2Progress(_skill2,SKILLTWO, SKILL2_CD_TIME, 2);
	}
}

void SkillShowLayer::skill1Progress(Sprite * sp,std::string name, float cdTime, int skillId)
{
	sp->setOpacity(100);
	auto pt = ProgressTimer::create(Sprite::create(name));
	pt->setPosition(sp->getPosition());
	auto pta = ProgressTo::create(cdTime,100);///  时间可以写成一个宏
	pt->setType(ProgressTimerType::RADIAL);
	auto cf = CallFunc::create([=](){
		sp->setOpacity(255);
		pt->removeFromParentAndCleanup(true);
	});
	pt->runAction(Sequence::create(pta,cf,CallFunc::create(CC_CALLBACK_0(SkillShowLayer::endSkill1Cd,this)),NULL));
	this->addChild(pt); 
}


void SkillShowLayer::skill2Progress(Sprite * sp,std::string name, float cdTime, int skillId)
{
	sp->setOpacity(100);
	auto pt = ProgressTimer::create(Sprite::create(name));
	pt->setPosition(sp->getPosition());
	auto pta = ProgressTo::create(cdTime,100);
	pt->setType(ProgressTimerType::RADIAL);
	auto cf = CallFunc::create([=](){
		sp->setOpacity(255);
		pt->removeFromParentAndCleanup(true);
	});
	pt->runAction(Sequence::create(pta,cf,CallFunc::create(CC_CALLBACK_0(SkillShowLayer::endSkill2Cd,this)),NULL));
	this->addChild(pt); 
}

void SkillShowLayer::skill3(Ref * obj)
{
	skill3Progress();
}

void SkillShowLayer::skill3Progress()
{
	_skill3->setOpacity(100);
	auto pt = ProgressTimer::create(Sprite::create(SKILLTHREE));
	pt->setPosition(_skill3->getPosition());
	auto pta = ProgressTo::create(10,100);
	pt->setType(ProgressTimerType::RADIAL);
	auto cf = CallFunc::create([=](){
		_skill3->setOpacity(255);
		pt->removeFromParentAndCleanup(true);
	});
	pt->runAction(Sequence::create(pta,cf,CallFunc::create(CC_CALLBACK_0(SkillShowLayer::endSkill3Cd,this)),NULL));
	this->addChild(pt); 
}

void SkillShowLayer::endSkill1Cd(){
	auto centerSkill = __NotificationCenter::getInstance();
	centerSkill->postNotification("Skill1Cd", this);
}

void SkillShowLayer::endSkill2Cd(){
	auto centerSkill = __NotificationCenter::getInstance();
	centerSkill->postNotification("Skill2Cd", this);
}

void SkillShowLayer::endSkill3Cd()
{
    auto bigSkillCd = __NotificationCenter::getInstance();
	bigSkillCd->postNotification("bigSkillCd", this);
}

//清除观察者
SkillShowLayer::~SkillShowLayer()
{
    auto centerSkill = __NotificationCenter::getInstance();
	centerSkill->removeObserver(this, "SkillType");
	auto bigSkillEnd = __NotificationCenter::getInstance();
	bigSkillEnd->removeObserver(this,"BigSkillEnd");
}


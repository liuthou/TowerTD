#include "BaseSkill.h"
#include "GameManager.h"

BaseSkill * BaseSkill::create(std::string filename,Vec2 curpoint ,Vec2 movepoint)
{  
	auto pef = new BaseSkill();
	if (pef&&pef->init(filename,curpoint,movepoint))
	{
		pef->autorelease();
		return pef;
	}
	CC_SAFE_DELETE(pef);
	return NULL;
}
bool BaseSkill::init(std::string filename,Vec2 &curpoint ,Vec2 &movepoint)
{
	if (!Sprite::initWithSpriteFrameName(filename))
	{
		return false;
	}
	//this->setScale(1.5);
	curTime = 0;
	this->duration = 10.0f;
	this->attack = 0.2f;
	this->state = 0;
	this->setPosition(curpoint);
	this->m_curpoint = curpoint;
	this->m_movepoint = movepoint;
	this->moveAnimate();
	this->attackAnimate();
	this->scheduleOnce(schedule_selector(BaseSkill::die),getDuration());//d will durate then remove;
	this->schedule(schedule_selector(BaseSkill::testBoundingWithEnemy));
	GameManager::getInstance()->getStageLayer()->getChildByName("tower")->addChild(this);
	GameManager::getInstance()->skillVector.pushBack(this);
	return true;
}
//skill attack animation
void BaseSkill::attackAnimate()
{
	this->schedule(schedule_selector(BaseSkill::skillRotateAnimate));
}
//skill move animation
void BaseSkill::moveAnimate()
{   
	float _distance = 0;
	if (!(_distance = m_curpoint.getDistance(m_movepoint)))
	{
		return;
	}
	auto _call = CallFunc::create([=](){this->die(0);}); 
	auto _jump = JumpTo::create(_distance/SKILLSPEED,m_movepoint,150,1);
	auto _sequ = Sequence::create(/*MoveTo::create(_distance/500,m_movepoint)*/_jump,_call,NULL);
	this->runAction(_sequ);
}
//remove 
void BaseSkill::removeSkill()
{   
	this->removeFromParentAndCleanup(true);
}
//when the skill end  
void BaseSkill::die(float t)
{   
	this->unscheduleAllSelectors();
	this->stopAllActions();
	GameManager::getInstance()->skillVector.eraseObject(this);
	auto _call = CallFunc::create([=](){this->removeSkill();});
	this->runAction(Sequence::create(dieAnimate(),_call,nullptr));
}
bool BaseSkill::boundHurt() //if the skill bounding with , run this,if skill only use once,return true,else return false
{
	die(0);
	return true;
}
//test boundingbox with  enemys
void BaseSkill::testBoundingWithEnemy(float t)
{   
	curTime = curTime + t;
	if (curTime > duration)
	{
		this->die(0);
		return;
	}
	auto &evector =GameManager::getInstance()->enemyVector;
	for (int i = 0;i < evector.size();i++)
	{   
	    auto enemy = evector.at(i);
		if (enemy->getLive() == DIE)
		{
			return;
		}
		if (enemy->getBoundingBox().intersectsRect(this->getBoundingBox()))
		{  
			enemy->hurt(this->getAttack(),(HurtState)getState());
			if (boundHurt())
			{
				break;
			}
		}
	}
}
void BaseSkill::skillRotateAnimate(float)//the skill rotate animate when this skill moved 
{
	float _angle = (m_movepoint - this->getPosition()).getAngle();
	this->setRotation(-CC_RADIANS_TO_DEGREES(_angle));
}
Animate *BaseSkill::dieAnimate()
{
	return Animate::create(Animation::create());
}
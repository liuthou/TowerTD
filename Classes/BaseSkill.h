#ifndef __BASESKILL_H
#define __BASESKILL_H
#include "cocos2d.h"
#include "GameBasic.h"
USING_NS_CC;
class BaseSkill:public Sprite
{
	CC_SYNTHESIZE(float,attack,Attack);
	CC_SYNTHESIZE_READONLY(int,state,State);  
	CC_SYNTHESIZE(float,duration,Duration)//duration time,this skill will run 
protected:
	float curTime;
	Vec2  m_curpoint;//this skill create in this postion
	Vec2  m_movepoint;//this skill will move to,if movepoint = curpoint this skill is  static 
	virtual void attackAnimate();
	virtual void moveAnimate();
	virtual void die(float t);
	virtual Animate* dieAnimate();
	void testBoundingWithEnemy(float t);
	void removeSkill();
	virtual void skillRotateAnimate(float);
	virtual bool boundHurt();
public:
	virtual bool init(std::string filename,Vec2 &curpoint ,Vec2 &movepoint);
	static BaseSkill * create(std::string filename, Vec2 curpoint ,Vec2 movepoint);	
};
#endif // !__BASESKILL_H

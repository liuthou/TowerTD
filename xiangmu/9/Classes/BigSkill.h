#ifndef __BIGSKILL_R_
#define __BIGSKILL_R_

#include "cocos2d.h"
#include "SkillBase.h"
using namespace cocos2d;

class BigSkill : public SkillBase
{
public:
	virtual bool init(Vec2 skillPoint);
	static BigSkill * create(Vec2 skillPoint);
	//实现大招技能的动画
	void skillAntimate();
	//移除大招技能
	void removeAntimate();
};

#endif
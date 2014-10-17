#ifndef  __LIGHTNING_R_
#define  __LIGHTNING_R_

#include "cocos2d.h"
#include "SkillBase.h"
using namespace cocos2d;

class Lightning : public SkillBase
{
public:
	virtual bool init(Vec2 skillPoint);
	static Lightning * create(Vec2 skillPoint);
	//实现闪电技能的动画
	void skillAntimate();
	//移除技能闪电
	void removeAntimate();
};

#endif
#ifndef __ARROWSKILL_H
#define __ARROWSKILL_H
#include "BaseSkill.h"
class ArrowSkill:public BaseSkill
{
public:
	virtual bool init(Vec2 &curpoint ,Vec2 &movepoint);
	static ArrowSkill * create(Vec2 curpoint ,Vec2 movepoint);
	Animate * dieAnimate();
};
#endif // !__ARROWSKILL_H

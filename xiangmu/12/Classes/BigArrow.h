#ifndef __BIGARROW_H
#define __BIGARROW_H
#include "ArrowSkill.h"
class BigArrow:public ArrowSkill
{
public:
	virtual bool init(Vec2 &curpoint ,Vec2 &movepoint);
	static BigArrow * create(Vec2 curpoint ,Vec2 movepoint);
	Animate * dieAnimate();
};
#endif // !__ARROWSKILL_H
#ifndef __BONESKILL_H
#define __BONESKILL_H
#include "BaseSkill.h"
class BoneSkill:public BaseSkill
{
public:
	virtual bool init(Vec2 &curpoint ,Vec2 &movepoint);
	static BoneSkill * create(Vec2 curpoint ,Vec2 movepoint);
	Animate * dieAnimate();
};
#endif // !__ARROWSKILL_H

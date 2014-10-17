#ifndef __ICESKILL_H
#define __ICESKILL_H
#include "BaseSkill.h"
class IceSkill:public BaseSkill
{
protected:	
	void moveAnimate();
	Animate * dieAnimate();
public:
	virtual bool init(Vec2 &curpoint ,Vec2 &movepoint);
	static IceSkill*create( Vec2 curpoint ,Vec2 movepoint);	
};
#endif // !__ICESKILL_H

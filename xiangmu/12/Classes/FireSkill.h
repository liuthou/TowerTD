#ifndef __FIRESKILL_H
#define __FIRESKILL_H
#include "IceSkill.h"
class FireSkill:public IceSkill
{   
protected:
	Animate* dieAnimate();
	void skillRotateAnimate(float);
public:
	virtual bool init(Vec2 &curpoint ,Vec2 &movepoint);
	static FireSkill* create(Vec2 curpoint ,Vec2 movepoint);
};
#endif // !__FIRESKILL_H

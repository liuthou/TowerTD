#ifndef __DOUBLETHUNDER_H
#define __DOUBLETHUNDER_H
#include "cocos2d.h"
#include "ThunderSkill.h"
USING_NS_CC;
class DoubleThunder:public ThunderSkill
{
public:
	virtual bool init(Vec2 &curpoint);
	static DoubleThunder * create(Vec2 curpoint);
	void attackAnimate();
};
#endif // !

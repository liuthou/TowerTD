#ifndef __WINDSKILL_H
#define __WINDSKILL_H
#include "ThunderSkill.h"
#include "cocos2d.h"
USING_NS_CC;
class WindSkill:public ThunderSkill
{  
protected:
	void attackAnimate();
	bool boundHurt();
public:
	virtual bool init(Vec2 &curpoint);
	static WindSkill * create(Vec2 curpoint);

};
#endif // !

#ifndef __THUNDERSKILL_H
#define __THUNDERSKILL_H
#include "cocos2d.h"
#include "BaseSkill.h"
USING_NS_CC;
class ThunderSkill:public BaseSkill
{   
	void attackAnimate();
	bool boundHurt();
	float &getDuration();
public:
	virtual bool init(Vec2 &curpoint);
	static ThunderSkill * create(Vec2 curpoint);
	
};
#endif // !

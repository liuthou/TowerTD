#ifndef __SUPERSKILL_H
#define __SUPERSKILL_H
#include "cocos2d.h"
#include "ThunderSkill.h"
#include "GameBasic.h"
enum superSkillType
{   
	SUPERFIRE = 1,
	SUPERICE,
	SUPERWIND,
	SUPERTHUNDER
};
typedef superSkillType SUPERSKILLTYPE;
class SuperSkill:public ThunderSkill
{   
	int type;
	void attackAnimate();
public:
	virtual bool init(Vec2 &curpoint,int type);
	static SuperSkill * create(Vec2 curpoint,int type);
};
#endif // !__SUPERSKILLTHUDNER_H

#ifndef __SKILLBASE_R_
#define __SKILLBASE_R_

#include "cocos2d.h"
using namespace cocos2d;

enum Driection1
{
	LEFT1,
	RIGHT1,
	JUMP1,
	NEARSKILL1,
	LEFTFARSKILL1,
	RIGHTFARSKILL1,
	BIGSKILL1,
	ATTACK1,
	STOP1
};

class SkillBase : public Sprite
{
public:
	//释放技能要消耗的MP
	CC_SYNTHESIZE(int, _consumeMp, ConsumeMp);
	//技能是否清除
	CC_SYNTHESIZE(bool,_isDie, IsDie);
	//技能的伤害值
	CC_SYNTHESIZE(int, _attack, Attack);
	virtual bool init(std::string name, Vec2 skillPoint);
    SkillBase() : _isDie(false){}
};

#endif
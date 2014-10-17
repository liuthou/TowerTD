#ifndef _BOSSTHREE_H
#define _BOSSTHREE_H
#include "cocos2d.h"
using namespace cocos2d;

class BossThree:public Sprite
{
public:
	int m_hp;
	int m_countToSkill;
	int m_skillType;
	int m_direction;
	void moveLeftAnimate();
	void moveRightAnimate();
	virtual bool init();
	CREATE_FUNC(BossThree);
	void move(float t);
	void callEnemy();
	void callFireBall();
	void callFire();
	void prepareForSkills(float t);
	void heroPKBoss(float t);
	
	void boss3hurt();
	void boss3die();

	Vec2 m_rollPosition;

};
#endif
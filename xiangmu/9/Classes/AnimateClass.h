#ifndef  __ANIMATECLASS_H
#define  __ANIMATECLASS_H

#include "cocos2d.h"
USING_NS_CC;
class AnimateClass :public Animate
{
public:
	virtual bool init();
	CREATE_FUNC(AnimateClass);
	//主角相关动画
	ActionInterval *heroRun();
	ActionInterval *heroAttack();
	ActionInterval *heroJumpAttack();
	ActionInterval *heroHurt();
	ActionInterval *heroDie();
	ActionInterval *heroSwordAnger();
	ActionInterval *heroLightningAnger();
	ActionInterval *heroStop();
	//技能动画
	ActionInterval *skillSwordAnger();
	ActionInterval *skillLightning();
	ActionInterval *skillBig();
	//敌人相关动画
	ActionInterval * monsterRun(int id);
	ActionInterval * monsterHurt(int id);
	ActionInterval * monsterAttack(int id);
	//哥布林行走动画
	ActionInterval * goblinRun();
	//哥布林受伤动画
	ActionInterval * goblinHurt();
	//哥布林攻击动画
	ActionInterval * goblinAttack();
	//南瓜行走动画
	ActionInterval * soldierRun();
	//南瓜受伤动画
	ActionInterval * soldierHurt();
	//南瓜攻击动画
    ActionInterval * soldierAttick();
	//牛头boos行走动画
	ActionInterval * boosRun();
	//牛头受伤动画
	ActionInterval * boosHurt();
	//牛头boos攻击动画
	ActionInterval * boosAttick();
};

#endif
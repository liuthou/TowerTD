#ifndef __MONSTERBASE_R_
#define __MONSTERBASE_R_

#include "cocos2d.h"
#include "AnimateClass.h"
#include <iostream>

using namespace std;
using namespace cocos2d;

enum MonsterState
{
	Partol,
	Pursuit,
	Attack,
	NULLPTR
};

class MonsterBase : public Sprite
{
private:
	void hurtHpAnimation();
public:
	CC_SYNTHESIZE(int, _hpValue, HpValue);
	CC_SYNTHESIZE(int, _attackValue, AttackValue);
	CC_SYNTHESIZE(float, _speedValue, SpeedValue);
	CC_SYNTHESIZE(int, _expValue, ExpValue);
	CC_SYNTHESIZE(bool, _monsterDie, MonsterDie);
	CC_SYNTHESIZE(bool,_monsterAttackState,MonsterAttackState);
	//怪物没发现主角，自己走
	void monsterPartol();
	//怪物发现主角
	void monsterPursuit();
	//清除所有的怪
	void cleanAllMonster();
	//怪物攻击主角
	void monsterAttack();
	void monsterHurt(int attack);
	void monsterDie();
	void monsterRemove();
	void monsterRunAnimation();
    void monsterAttackAnimation();
	void monsterHurtAnimation();
	void monsterDieAnimation() ;
	void monsterHpSprite();
	virtual bool initWithSpriteFrameName(std::string monsterName, int hp, int attack, int id, float speed, int exp);
	//每帧发送消息
	void update(float t);
	MonsterBase():_isHurt(false){}
	~MonsterBase();
private:
	//调用一次
	bool _isOnePartol;
	bool _isRun;
	bool _isHurt;
	MonsterState beforeSendState;
	MonsterState curState;
	Sprite * hero;
	int _id;
	int counts;
	ProgressTimer* progress;
	int allHp;
	AnimateClass * _animateClass;
	int _hurtAttackValue;
};

#endif

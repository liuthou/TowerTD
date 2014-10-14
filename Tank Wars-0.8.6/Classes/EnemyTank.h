#ifndef __ENEMYTANK_H
#define __ENEMYTANK_H
#include "cocos2d.h"
#include "BaseTank.h"
using namespace cocos2d;
class EnemyTank:public BaseTank{
protected:
	Vec2 position;
	//敌方坦克移动
	virtual void Enemymove(float t);
	//敌坦克的智能移动和开火
	virtual void update(float t);
	virtual void playMoveEffect();
	void EnemyTestBounding(float t);
public:
//	virtual void move(moverect State);//敌坦克的移动方法
	virtual bool initWithSpriteFrameName(std::string name,int hp,int speed,Vec2 position);
	virtual void fire();//敌坦克的开火方法
	virtual  void runAnimate();
	CREATE_FUNC(EnemyTank);
	
};
#endif
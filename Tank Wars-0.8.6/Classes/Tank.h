#ifndef __TANK_H
#define __TANK_H
#include "cocos2d.h"
#include "BaseTank.h"
#define TANKHP 500
#define SPEED 80
using namespace cocos2d;
class Tank:public BaseTank{
	void playMoveEffect();
public:
	virtual void fire();//开火方法
	virtual  void runAnimate();//运行动画
	virtual bool init();
	static Tank* create();
};
#endif
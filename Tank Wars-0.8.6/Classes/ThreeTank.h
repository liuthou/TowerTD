#ifndef __THREETANK_H
#define __THREETANK_H
#include "cocos2d.h"
#include "EnemyTank.h"
#define THREEHP 300
#define THREESPEED 100
using namespace cocos2d;
class ThreeTank: public EnemyTank{
public:
	virtual bool init(Vec2 position);
	//‘À––∂Øª≠
	virtual  void runAnimate();
	static ThreeTank* create(Vec2 position);
};
#endif
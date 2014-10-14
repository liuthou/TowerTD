#ifndef __ONETANK_H
#define __ONETANK_H
#include "cocos2d.h"
#include "EnemyTank.h"
#define ONEHP 100
#define ONESPEED 50
using namespace cocos2d;
class OneTank:public EnemyTank{
public:
	virtual bool init(Vec2 position);
	//‘À––∂Øª≠
	virtual  void runAnimate();
	static OneTank* create(Vec2 position);
};
#endif
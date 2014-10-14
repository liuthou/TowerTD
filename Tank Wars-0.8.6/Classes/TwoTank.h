#ifndef __TWOTANK_H
#define __TWOTANK_H
#include "cocos2d.h"
#include "EnemyTank.h"
#define TWOHP 200
#define TWOSPEED 75
using namespace cocos2d;
class TwoTank:public EnemyTank{
public:
	virtual bool init(Vec2 position);
	//‘À––∂Øª≠
	virtual  void runAnimate();
	static TwoTank* create(Vec2 position);
};
#endif
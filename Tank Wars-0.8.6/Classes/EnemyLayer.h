#ifndef __ENEMYLAYER_H
#define __ENEMYLAYER_H
#include "cocos2d.h"
using namespace cocos2d;
class EnemyLayer:public Layer{
public:
	void onEnter();
	virtual bool init();
	CREATE_FUNC(EnemyLayer);
	//产生坦克
	virtual void Outtank();
private:
	//敌坦克的产生回调
	virtual void update(float t);
	bool isHaveTank(Vec2  postion);//此方法中判定,是否可产生TANK
};
#endif
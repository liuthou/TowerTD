#ifndef __BACEBULLET_H
#define __BACEBULLET_H
#include "cocos2d.h"
//子弹移动速度
#define BULLETSPEED 1000
using namespace cocos2d;
class BaseBullet:public Sprite
{
public:
	virtual bool initWithSpriteFrameName(std::string name,Vec2 position,int speed);
public:
	//攻击力
	CC_SYNTHESIZE_READONLY(int ,attackValue,AttackValue);
	//速度
	CC_SYNTHESIZE_READONLY(int ,speed,Speed);
	virtual void remove();
};

#endif
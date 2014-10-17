#ifndef __PowerfulTower_H
#define __PowerfulTower_H
#include "cocos2d.h"
#include "Tower.h"
#include "Bullet.h"
USING_NS_CC;

class PowerfulTower:public Tower{
public:
	static PowerfulTower*create(int id);
	virtual void fire(Sprite* monster);

};
#endif
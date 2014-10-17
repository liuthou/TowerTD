#ifndef __DINOSAURBULLET_H
#define __DINOSAURBULLET_H
#include "cocos2d.h"
using namespace cocos2d;
#include "BaseBullet.h"
#define DINOSAURSPEED 200
#define DINOSAURBULLET "shitou.png"
class DinosaurBullet:public BaseBullet
{
protected:
	virtual bool init(Vec2 position,int attack);
public:
	static DinosaurBullet *create(Vec2 position,int attack);
	virtual void move();
};
#endif
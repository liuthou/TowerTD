#ifndef __ROLEONEBULLET_H
#define __ROLEONEBULLET_H
#include "cocos2d.h"
using namespace cocos2d;
#include "BaseBullet.h"
#define IMAGENAME "roleBullet.png"
#define ROLEBULLETSPEED 200
class RoleOneBullet:public BaseBullet
{
protected:
	virtual bool init(Vec2 position,int attack);
	virtual void move();
public:
	static RoleOneBullet *create(Vec2 position,int attack);
};
#endif
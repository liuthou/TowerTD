#ifndef __ENEMYONEBULLET_H
#define __ENEMYONEBULLET_H
#include "cocos2d.h"
#include "BaseBullet.h"
using namespace cocos2d;
#define ATTACK 50
#define SPEED 200
class EnemyOneBullet:public BaseBullet
{
protected:
	virtual bool init(Vec2 position,int attack);
public:
	static EnemyOneBullet *create(Vec2 position,int attack);
	virtual void move();
};
#endif
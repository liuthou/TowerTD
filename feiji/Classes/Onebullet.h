#ifndef __ONEBULLET_H
#define __ONEBULLET_H
#include "Bacebullet.h"
#include "cocos2d.h"
#define ONEATTACKVALUE 100
using namespace cocos2d;
class OneBullet:public BaseBullet
{
public:
	virtual bool init(Vec2 position);
	static OneBullet* create(Vec2 position);
};
#endif
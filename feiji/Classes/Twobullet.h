#ifndef __TWOBULLET_H
#define __TWOBULLET_H
#include "Bacebullet.h"
#include "cocos2d.h"
#define TWOATTACKVALUE 100
using namespace cocos2d;
class TwoBullet:public BaseBullet
{
public:
	virtual bool init(Vec2 position);
	static TwoBullet*create(Vec2 position);

};
#endif
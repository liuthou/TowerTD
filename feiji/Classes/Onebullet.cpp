#include "OneBullet.h"
bool OneBullet::init(Vec2 position)
{
	if(!BaseBullet::initWithSpriteFrameName("bullet1.png",position,BULLETSPEED))
	{
		return false;
	}
	attackValue =ONEATTACKVALUE;
	return true;
}
OneBullet *OneBullet::create(Vec2 position)
{
	OneBullet *one =new OneBullet();
	if(one && one->init(position))
	{
		one->autorelease();
		return one;
	}
	CC_SAFE_DELETE(one);
	return nullptr;
}


#include "TwoBullet.h"
bool TwoBullet::init(Vec2 position)
{
	if(!BaseBullet::initWithSpriteFrameName("bullet2.png",position,BULLETSPEED))
	{
		return false;
	}
	attackValue =TWOATTACKVALUE;
	return true;
}
TwoBullet *TwoBullet::create(Vec2 position)
{
	TwoBullet *two =new TwoBullet();
	if(two && two->init(position))
	{
		two->autorelease();
		return two;
	}
	//°²È«ÊÍ·Å
	CC_SAFE_DELETE(two);
	return nullptr;
}


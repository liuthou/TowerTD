#ifndef __BULLETS_H
#define __BULLETS_H
#include "cocos2d.h"
#include "Bacebullet.h"
using namespace cocos2d;
class Bullets
{
private:
	Bullets(){}
	Bullets(const Bullets & b){}
	Bullets operator =(const Bullets & b)
	{
		return b;
	}
protected:
	static Bullets *instance;
public:
	Vector<BaseBullet *>bulletsVector;
	static Bullets * getInstance();
	void addBullet(BaseBullet * bt);
	void deleteBullet(BaseBullet* bullet);
};
#endif
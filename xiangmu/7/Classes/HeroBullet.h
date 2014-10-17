#ifndef _HEROBULLET_H
#define _HEROBULLET_H
#include "BaseBullet.h"

#define BULLETSPEED 250

class HeroBullet : public BaseBullet
{
public:
	virtual bool init(std::string fileName,Vec2 position);		//重写init函数
	static HeroBullet *create(std::string fileName,Vec2 position);		//重写create函数
	void move(int direction);
};


#endif
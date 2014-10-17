#ifndef __BASEBULLET_H
#define __BASEBULLET_H
#include "cocos2d.h"
using namespace cocos2d;
class BaseBullet:public Sprite
{
public:
	int getAttack();
	void deleteMy();
	void setIsDie();
	bool getIsDie();
protected:
	virtual bool init(std::string fileName,Vec2 positionBegin,int attack,int speed);
	Vec2 position;
	int attack;
	int speed;
	bool isDie;
	virtual void move() = 0;
};
#endif
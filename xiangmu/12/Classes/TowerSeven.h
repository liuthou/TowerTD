#ifndef __TOWERSEVEN_H
#define __TOWERSEVEN_H
#include "cocos2d.h"
#include "BaseTower.h"
USING_NS_CC;
class TowerSeven:public BaseTower
{
	TowerSeven(){this->curgold = TOWERSEVENCOST;}
public:
	CREATE_FUNC(TowerSeven);
	virtual bool init();
	
	virtual void Attack(float t);	 
	virtual void stopAnm();
};
#endif
#ifndef __TOWERSIX_H
#define __TOWERSIX_H
#include "cocos2d.h"
#include "BaseTower.h"
USING_NS_CC;
class TowerSix:public BaseTower
{   
	TowerSix(){this->curgold = TOWERSIXCOST;}
public:
	CREATE_FUNC(TowerSix);
	virtual bool init();
	virtual void Attack(float t);	 
	virtual void stopAnm();
};
#endif
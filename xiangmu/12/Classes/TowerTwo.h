#ifndef __TOWERTWO_H
#define __TOWERTWO_H
#include "cocos2d.h"
#include "BaseTower.h"
USING_NS_CC;
class TowerTwo:public BaseTower
{
	TowerTwo(){this->curgold = TOWERTWOCOST;}
public:
    CREATE_FUNC(TowerTwo);
	virtual bool init();

	virtual void Attack(float t);	 
	virtual void stopAnm();
};
#endif
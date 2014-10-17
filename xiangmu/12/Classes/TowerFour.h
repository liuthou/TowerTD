#ifndef __TOWERFOUR_H
#define __TOWERFOUR_H
#include "cocos2d.h"
#include "BaseTower.h"
 
using namespace cocos2d;

class TowerFour:public BaseTower
{  
	TowerFour(){this->curgold = TOWERFORECOST;};
public:
	CREATE_FUNC(TowerFour);
	virtual bool init();

	virtual void Attack(float t);	 
	virtual void stopAnm();
};
#endif
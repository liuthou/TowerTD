#ifndef __TOWERONE_H
#define __TOWERONE_H
#include "cocos2d.h"
#include "BaseTower.h"
using namespace cocos2d;

class TowerOne:public BaseTower
{   
	TowerOne(){this->curgold = TOWERONECOST;}
public:
	CREATE_FUNC(TowerOne);
	virtual bool init();
	 
	virtual void Attack(float t);	 
	virtual void stopAnm();
};
#endif
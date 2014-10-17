#ifndef __TOWERFIVE_H
#define __TOWERFIVE_H
#include "cocos2d.h"
#include "BaseTower.h"

using namespace cocos2d;

class TowerFive:public BaseTower
{  
	TowerFive(){this->curgold = TOWERFIVECOST;}
public:
	CREATE_FUNC(TowerFive);
	virtual bool init();

	virtual void Attack(float t);	 
	virtual void stopAnm();

};
#endif
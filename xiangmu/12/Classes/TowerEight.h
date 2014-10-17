#ifndef __TOWEREIGHT_H
#define __TOWEREIGHT_H
#include "cocos2d.h"
#include "BaseTower.h"

using namespace cocos2d;

class TowerEight:public BaseTower
{
	TowerEight(){this->curgold = TOWEREIGHTCOST;}
public:
	CREATE_FUNC(TowerEight);
	virtual bool init();

	virtual void Attack(float t);	 
	virtual void stopAnm();
};
#endif
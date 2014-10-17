#ifndef __TOWERTHREE_H
#define __TOWERTHREE_H
#include "cocos2d.h"
#include "BaseTower.h"
USING_NS_CC;
class TowerThree:public BaseTower
{   
	TowerThree(){this->curgold = TOWERTHREECOST;}
public:
	CREATE_FUNC(TowerThree);
	virtual bool init();

	virtual void Attack(float t);	 
	virtual void stopAnm();
};
#endif
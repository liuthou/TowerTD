#ifndef __TOWERAI_H_
#define __TOWERAI_H_
#include "cocos2d.h"
using namespace cocos2d;
class Tower;
class Enemy;
class TowerAI:public Node{
public:
	
	static TowerAI* create(Tower* tower);
	virtual bool init(Tower* tower);
	
protected:
	CC_SYNTHESIZE(Tower*,tower,Tower);
	CC_SYNTHESIZE(float,firespeed,FireSpeed);
	void checkfire(float dt);
	void onEnter();
};
#endif
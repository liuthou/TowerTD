#ifndef __TOWERLAYER_H
#define __TOWERLAYER_H
#include "cocos2d.h"
using namespace cocos2d;

class Towerlayer:public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(Towerlayer);
		void addTower(int towerType, Vec2 buildPos);
	Vec2 checkPoint;
	//Éý¼¶·½·¨
	virtual void checkUpdate(Vec2 point);
    bool checkIsBuild(Vec2 position);

};
#endif
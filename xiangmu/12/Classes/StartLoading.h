#ifndef __STARTLOADING_H
#define __STARTLOADING_H
#include "cocos2d.h"
#include "GameBasic.h"
using namespace cocos2d;

class StartLoading:public Layer{
	
	int armCount;
	void addSprite();
public:
	virtual bool init();
	CREATE_FUNC(StartLoading);
	static Scene *createScene();
	void loadingArm(float t);
};
#endif
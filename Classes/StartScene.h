#ifndef __STARTSCENE_H
#define __STARTSCENE_H
#include "cocos2d.h"
#include "GameBasic.h"
using namespace cocos2d;
class StartScene:public Layer{
public:
	virtual bool init();
	CREATE_FUNC(StartScene);
	static Scene *createScene();
};
#endif

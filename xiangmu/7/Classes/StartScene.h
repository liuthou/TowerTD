#ifndef __STARTSCENE_H_
#define __STARTSCENE_H_
#include "cocos2d.h"
using namespace cocos2d;

class StartScene :public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(StartScene);

	virtual void onEnter();

};
#endif
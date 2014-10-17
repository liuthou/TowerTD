#ifndef __PAUSELAYER_H
#define __PAUSELAYER_H
#include "cocos2d.h"
#include "GameBasic.h"
using namespace cocos2d;
class PauseLayer:public Layer{
public:
	virtual bool init();
	CREATE_FUNC(PauseLayer);
};
#endif
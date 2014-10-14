#ifndef __MAINPLANLAYER_H
#define __MAINPLANLAYER_H
#include "cocos2d.h"
using namespace cocos2d;
class MainplanLayer:public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(MainplanLayer);
};

#endif
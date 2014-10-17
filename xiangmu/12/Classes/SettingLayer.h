#ifndef __SETTINGLAYER_H
#define __SETTINGLAYER_H
#include "cocos2d.h"
using namespace cocos2d;
class SettingLayer:public Layer{
public:
	virtual bool init();
	CREATE_FUNC(SettingLayer);
};
#endif
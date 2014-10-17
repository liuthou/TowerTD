//放置背景(后期可以添加特效)
#ifndef __BACKGROUNDLAYER_H_
#define __BACKGROUNDLAYER_H_
#include "cocos2d.h"
using namespace cocos2d;
class BackgroundLayer:public Layer{
public:
	CREATE_FUNC(BackgroundLayer);
	virtual bool init();
	//onEnter根据当前关卡换背景(代码好烂不忍直视)
	virtual void onEnter();
};
#endif
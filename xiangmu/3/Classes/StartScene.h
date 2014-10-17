#ifndef __StartScene_H
#define __StartScene_H
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio;
class StartScene:public Scene{
public:
	virtual bool init();
	CREATE_FUNC(StartScene);
	RepeatForever* MyPathFun();
	Widget* layer;
	virtual void onEnter();
	Widget* addHelpLayer();
};

#endif
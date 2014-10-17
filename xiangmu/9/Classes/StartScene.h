#ifndef __STARTSCENE_H__
#define __STARTSCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace cocostudio;
using namespace cocos2d::ui;

class StartScene :public Layer
{
protected:
	virtual bool init();
public:
	CREATE_FUNC(StartScene);
	static Scene *createScene();
};

#endif
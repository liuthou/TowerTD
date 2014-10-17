#ifndef __BACKLAYER_H__
#define __BACKLAYER_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace cocostudio;
using namespace cocos2d::ui;

class BackLayer :public Layer
{
protected:
	virtual bool init();
public:
	CREATE_FUNC(BackLayer);
};

#endif
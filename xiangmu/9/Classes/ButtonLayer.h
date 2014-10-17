#ifndef __BUTTONLAYER_H__
#define __BUTTONLAYER_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace cocostudio;
using namespace cocos2d::ui;

class ButtonLayer :public Layer
{
protected:
	 Size vSize;
public:	
	virtual bool init();
	CREATE_FUNC(ButtonLayer);	
};

#endif
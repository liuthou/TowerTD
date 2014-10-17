#ifndef __GAMEOVERLAYER_H__
#define __GAMEOVERLAYER_H__
#include "cocos2d.h"
using namespace cocos2d;
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocostudio;
using namespace ui;

class GameOverLayer :public Layer
{
public:	
	CREATE_FUNC(GameOverLayer);	
protected:
	virtual bool init();
};
#endif
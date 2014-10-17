#ifndef __GAMEFINISHLAYER_H
#define __GAMEFINISHLAYER_H

#include "cocos2d.h"
#include "HeroBase.h"
USING_NS_CC;
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocostudio;
using namespace ui;

class GameFinishLayer :public Layer
{
private:
	HeroBase * _heroBase;
public:
	virtual bool init();
    CREATE_FUNC(GameFinishLayer);
private:
	void heroWriteInDataCache();
};

#endif
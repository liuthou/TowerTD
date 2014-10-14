#ifndef __UILAYER_H
#define __UILAYER_H
#include "cocos2d.h"
#include "cocoStudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocostudio;
using namespace ui;

class UiLayer : public Layer{
	int curhomehp;//老窝初始血量
	int curmoney;//初始金钱数
	int waves;//怪物总波数
	int shuts;//第几关
	int totalwaves;//共几波
	Widget * uilayer;
	TextBMFont * wave;//波数and怪数
	TextBMFont * money;//金钱数
	TextBMFont * homehp;//老窝血量
	virtual void setMoney(Ref * sender);
	virtual void setHomehp(Ref * sender);
	virtual void setWave(Ref * sender);
	virtual void updateTower(Ref* sender);
	virtual void removeTower(Ref* sender);
public:
	UiLayer();
	~UiLayer();
	virtual int getcurmoney();
	virtual bool init();
	CREATE_FUNC(UiLayer);
};
#endif

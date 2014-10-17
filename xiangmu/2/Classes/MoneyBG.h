#ifndef __MONEYBG_H
#define __MONEYBG_H
#include "cocos2d.h"

using namespace cocos2d;

class MoneyBG :public Layer
{
private:
	Sprite * bg;
	Menu * menuItem;
	Sprite * BG;
public:
	virtual bool init();
	CREATE_FUNC(MoneyBG);
	static Scene * createScene();
	void back(Ref * sender);
};
#endif
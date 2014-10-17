
#ifndef __Dota_Legend__ChangeLayer__
#define __Dota_Legend__ChangeLayer__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;
class ChangeLayer :public Layer {
protected:
	void allowChangeHero();
	bool flag;
	Menu * menu; //选中的菜单
	Menu * heromenu;
	//滑动的位置
	Vec2 point;

	//三个初始的位置
	Vec2 hero1point;
	Vec2 hero2point;
	Vec2 hero3point;

	//屏幕的长宽
	float bgX;
	float bgY;
	Sprite * decisionWindow;
public:
	Vector<MenuItemImage*> menuItemImage;//开关按钮子项的数组
	Vector<MenuItemToggle*> menuItemToggle;//开关数组
	void changeHeroItem(Ref * sender);
	void changeOver(Ref * sender);
	virtual bool init();
	CREATE_FUNC(ChangeLayer);
};
#endif /* defined(__Dota_Legend__ChangeLayer__) */

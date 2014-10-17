
#ifndef __Dota_Legend__AttackLayer__
#define __Dota_Legend__AttackLayer__

#include <stdio.h>
#include "cocos2d.h"


USING_NS_CC;
class AttackLayer : public Layer {
protected:
	float bgX;
	float bgY;
	void addHeroWindow();
	void stopLayer(Ref * sender);
	//通往下一场景的按钮
	void nextMap(Ref * sender);
	//退出按钮回调
	void EndMenu(Ref * sender);
	//自动战斗
	void automaticAttack(Ref * sender);
	//遮罩层
	Sprite * shield;
	//存放英雄的窗口
	Sprite * herowindow;
	//
	 MenuItemImage *nextitem;
	Sprite *bg;
public:
	virtual bool init();
	CREATE_FUNC(AttackLayer);
	void setNextMapVisable(bool isVisible);
	void setBg(std::string TexName);
	void menuCallback(Ref * sender);
	void popGameScene(Ref* sender);
};
#endif /* defined(__Dota_Legend__AttackLayer__) */

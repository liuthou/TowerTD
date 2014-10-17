#ifndef __TexasPoker__DealingPokersAnimation__
#define __TexasPoker__DealingPokersAnimation__

#include "cocos2d.h"
USING_NS_CC;

#include "PokerAnimation.h"
#include "ui/UILoadingBar.h"
#include "ui/CocosGUI.h"
using namespace ui;


class RaiseAnimation : public PokerAnimation{
public:
	virtual bool init();

	CREATE_FUNC(RaiseAnimation);
private:
	//推送按钮函数，将要加注的筹码值赋给成员变量chip
	void pushButton();

private:
	Sprite * raise_1;

	Sprite * raise_4;

	//按钮初始位置
	Point initPosition;

	//黄色变色条
	LoadingBar * yellowScrol;

	//通过按钮所选的筹码数
	int chip;
	
};
#endif

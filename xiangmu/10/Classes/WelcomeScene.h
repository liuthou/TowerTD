#pragma once

#include "AppMacro.h"

#define BG_PATH "welcomeBg.png"
#define START_BTN_POS Vec2(VSIZE.width/2, 300)

/*
**欢迎场景
**
**这个场景只在第一次安装的时候出现一次

	
**
*/
class WelcomeScene : public Scene {
private:
	//背景图片
	Sprite *m_sp;

	Sprite *m_selector;
protected:
	bool init();

	void initBg();

	// 跳转到主场景
	void goStart(Ref *sender);	// 需要实现的函数 ： 跳转到主场景MainScene
public:
	CREATE_FUNC(WelcomeScene);
	void onEnter() override;
};
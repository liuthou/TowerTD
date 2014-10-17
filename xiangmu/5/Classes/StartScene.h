#ifndef __STARTSCENE_H_
#define __STARTSCENE_H_
#include <cocos2d.h>
using namespace cocos2d;

class StartScene : public Layer
{
private:
	Sprite *backGround;	 //背景图
	Sprite *gameLogo;	 //游戏Logo
	Sprite *prompt;		 //提示
	Sprite *kelchend;	 //奖杯
	Sprite *ribbon;		 //奖章
	MenuItemImage *startItem;	//开始按钮
	MenuItemImage *audioItem;	//音量按钮
	MenuItemImage *aboutItem;	//关于按钮
	int audioFlag;		//音量开关
	void addAboutItem();
	void addSprite(Sprite *sp, std::string fileName, Vec2 p);
	void addMenu(MenuItemImage *item,std::string normalName, std::string selName, Vec2 p, bool toggleFlag);
	void onEnter();

public:
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(StartScene);
};
#endif
#ifndef __SUSPENDLAYER_H_
#define __SUSPENDLAYER_H_
#include "cocos2d.h"
USING_NS_CC;

class SuspendLayer : public Layer{
public:
	CREATE_FUNC(SuspendLayer);
protected:
	//添加精灵，参数为：图片文件名，位置，缩放比例
	void addSprite(std::string fileName, Vec2 spritePos, float scaleValue);
	//添加按钮，参数为：显示图片，选择图片，位置，是否是开关，回调函数
	void addMenu(std::string norName, std::string selName, Vec2 itemPos, bool toggleFlag, std::function<void (Ref *)> menuCallback);
	//回到开始界面按钮回调函数
	void toStartScene(Ref * sender);
	//转到帮助界面按钮回调函数
	void toHelpLayer(Ref * sender);
	//继续游戏按钮回调函数
	void backToGame(Ref * sender);
	virtual bool init();
	//添加touch事件，并吞噬touch事件
	void addTouch();

protected:
	int audioFlag;
};

#endif // !__SUSPENDLAYER_H_

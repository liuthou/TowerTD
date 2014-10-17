#ifndef __SelectScene_H
#define __SelectScene_H
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace ui;
class SelectScene:public Scene{
public:
	virtual bool init();
	CREATE_FUNC(SelectScene);
	virtual void onEnter();
	CC_SYNTHESIZE(int,passedchapter,PassedChapter);
protected:
	Vector<Node*> buttons;
	void addTouchEventListener(Ref*sender,Widget::TouchEventType t);//点击选关按钮回调的函数
	int buttonIndex;
	PageView * page1;
	int pageIndex;
	void nextPage(Ref* sender,Widget::TouchEventType t);//pageView换层的函数
	void returnLastScene(Ref* sender,Widget::TouchEventType t);//返回按钮的回调函数
	void setButtonTexture(int buttonIndex,std::string fileName,int tagnum);//未受到全面保护
	//读取过关状态并修改按钮
	void readUserMessage();
	SelectScene(){
		buttonIndex = 1;
		pageIndex =0;
	}
};
#endif
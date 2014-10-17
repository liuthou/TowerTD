#ifndef __MonsterGuide 
#define __MonsterGuide
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocostudio;
using namespace ui;
class MonsterGuide :public Layer{
public:
	virtual bool init();
	CREATE_FUNC(MonsterGuide);
	static Scene* createScene();
	virtual void onEnter();
	Vector<Node*>buttons;//得到UI界面Button数组
	Widget* layer;
protected:
	Vector<Sprite*> guideSprite;//得到包含怪物信息图片的精灵数组
	void guideTouch(Ref* sender,Widget::TouchEventType t);//button的回调方法
	void operateLayerVector(int index);//对怪物信息图片数组进行操作
};
#endif
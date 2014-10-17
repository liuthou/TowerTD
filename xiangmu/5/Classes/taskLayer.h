#ifndef __TASKLAYER__H
#define __TASKLAYER__H
#include "cocos2d.h"
USING_NS_CC;

class taskLayer : public Layer
{
public:
	CREATE_FUNC(taskLayer);

protected:
	virtual bool init();
	void onEnter();

	//更改Label显示,更换黄匡
	void changeDisplay(std::string name);
	
	//添加任务所要解锁道具
	void addTool();

	//添加任务框以及Label、箭头
	void addSprite();

	//处理接收的通知
	void testMessage(Ref * message);

	//显示任务
	void showTask();

	//设置Label显示
	void setLabel();

	virtual ~taskLayer();
	

private:
	int audioFlag;
	//任务框
	Sprite * conditionIcon_1;
	Sprite * conditionIcon_2;
	Sprite * conditionIcon_3;

	//任务框下的Label
	Label * conditionLabel_1;
	Label * conditionLabel_2;
	Label * conditionLabel_3;

	//任务所要解锁的道具
	Sprite * taskTool;

	int count;

	//任务所用到的所有条件
	ValueMap allCondition; 

	//任务框
	Vector<Sprite *> conditionIcons;

	//任务所需精灵的集合
	Vector<Sprite *> taskSprites;

	//所显示的3个Label
	Vector<Label *> labels;
};

#endif
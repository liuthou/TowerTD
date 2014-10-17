#ifndef __TOUCHLAYER_H_
#define __TOUCHLAYER_H_
#include "cocos2d.h"
#include "Tower.h"
USING_NS_CC;
class TouchLayer:public Layer{
private:
	bool Pstate;//是否已设置精灵位置
	void setPstate();
	void onEnter();
	Sprite *tmpsp;
	
	Vector<Sprite*> towerbutton;
	//初始化放塔按钮
	void initTowerButton();
	void createTower();
	//放置放塔按钮的层
	Layer* towerbuttonlayer;
	Vec2 beganPosition;
	Vec2 tiledPosition;//落点图块位置
	//格式化工具button
	Sprite* formatbutton;
	std::function<bool(int)> cutscore;

	//创建塔时扣分的函数
	bool spendMoney(int money);
	//直接修改地图上的GID(设计的真烂,以后再说吧)
	void changeGID(Vec2 towerPosition);
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
public:
	CREATE_FUNC(TouchLayer);
	virtual bool init();
	void setCutScore(std::function<bool(int)> cutscore);
public:
	 void setTouchStop(bool isStop);
};
#endif
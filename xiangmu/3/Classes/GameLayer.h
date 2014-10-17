//塔,怪,子弹所在的层
#ifndef __GAMELAYER_H_
#define __GAMELAYER_H_
#include "cocos2d.h"
USING_NS_CC;
class GameLayer:public Layer{
public:
	CREATE_FUNC(GameLayer);
	virtual bool init();
	void onEnter();
	void onExit();
protected:
	//在帧回调中碰撞检测
	void update(float dt);
};
#endif
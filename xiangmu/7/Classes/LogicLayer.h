#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class LogicLayer:public Layer{

public: 
	virtual bool init();
	CREATE_FUNC(LogicLayer);

	//英雄的子弹和 小鬼碰撞
	void heroBulletPKenemy(float t);


	//英雄和道具的碰撞
	void heroPKtool(float t);

	//删除所有的子弹
	void deleteAllObject();

	void onEnter();

	//当本关的敌人死光光后 进行跳转到下一关
	void turnToNextScene(float t);

	//主角的子弹与敌人的子弹
	void heroBulletsPKenemysBullets(float t);

	void heroPKenemyBullets(float t);

	void update(float t);


};
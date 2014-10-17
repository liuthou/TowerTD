#pragma once

#include "AppMacro.h"
#include "BaseLayer.h"

#define BG_MOVE_SPEED 60

class MainPlane;

class GameLayer : public BaseLayer{
protected:
	Sprite *m_bg1;

	Sprite *m_bg2;

	float m_bjHight;

	MainPlane *m_mainPlane;

	virtual bool init();
public:
	CREATE_FUNC(GameLayer);

	//开始游戏
	void start();

	// 暂停
	void stop();

	//重置函数
	void reset();
private:
	/* 开始产生物体 */
	void startProp();

	void startMainPlane();

	void startEnemy();

	void startBg();

	/* 结束 */
	void endProp();

	void endMainPlane();

	void endEnemy();

	void endBg();

	void initMainPlane();

	void initBg();

	/* 背景滚动 */
	void update(float t);

	/* 产生道具的回调函数 */
	void newProp(float t);

	/* 产生敌机的回调函数 */
	void newEnemy(float t);
};
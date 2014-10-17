#pragma once

#include "AppMacro.h"
#include "BaseLayer.h"


/*
	及时分数层
	
	在屏幕右上角有一个标签显示着当前游戏时间
	
	当接收到"game_start"时，update函数开启，时间会一直累计
	
	当接收到"game_over"时， update函数关闭，时间终止计时
*/
class ScoreLayer : public BaseLayer {
private:
	float m_time;	// counting time of game
	Label *m_timeLbl;
	Label *m_lb;
	int m_promTime;
protected:
	bool init();
public:
	CREATE_FUNC(ScoreLayer);
public:
	/*
		每帧累计游戏时间
	*/
	void update(float dt);
	
	/* 开始计时 */
	void start();
	
	/* 停止计时 */
	void stop();
	
	/* 重置函数 */
	void reset();
	
	/* 获得当前分数 */
	float getScore();
	//添加计时层
	void addTimeLabel();
	//添加计分回调
	void countTime(int t);
};

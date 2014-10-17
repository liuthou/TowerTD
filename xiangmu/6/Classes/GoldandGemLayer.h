//
//GoldandGemLayer.cpp
//
//
//create by lius   9ÔÂ23ÈÕ
//
//
#ifndef __GOLDANDGEMLAYER_H_
#define __GOLDANDGEMLAYER_H_
#include "cocos2d.h"
#include "BackgroundLayer.h"
using namespace cocos2d;
class GoldandGemLayer:public Layer{
protected:
	BackgroundLayer * ulayer;
	Size vSize;
	//location x
	int m_id_x;
	//location y
	int m_id_y;
	//role jump height
	float m_height;
public:
	void monitorHeight(float t);
	void coinShape();
	//appear coin
	void appearCoin();
	//add meters
	void addMeters();
	void onEnter();
	virtual bool init();
	CREATE_FUNC(GoldandGemLayer);
};
#endif
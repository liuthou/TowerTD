#ifndef __ENEMYLAYER_H
#define __ENEMYLAYER_H
#include "cocos2d.h"
#define DAFEIJISPEED 80
#define QUICKSPEED 400
#define BASEPLANSPEED 150
using namespace cocos2d;
class Enemylayer:public Layer{
public:
	virtual bool init();
	CREATE_FUNC(Enemylayer);
protected:
	//时间成员变量定时增加
	int t;//0
	//出现快飞机的概率
	int quickf;//5
	//出现大飞机的概率
	int bigf;//0.1
	//时间级别,20,40,80,160
	unsigned long levelt;
	//进入下一级别
	void nextlevel();
	//每秒回调一次
	void addtime(float t);
	//桢回调
	void update(float t);
	//出飞机
	void go();
	//出飞机时间
	float outplane;
	//出飞机累计时间超过开始出现飞机
	float outsum;

};
#endif
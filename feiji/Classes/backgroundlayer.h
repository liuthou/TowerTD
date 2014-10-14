#ifndef __BACKGROUNDLAYER_H
#define __BACKGROUNDLAYER_H
//背景下滚动速度(n/秒 )。
#define BGDOWNSPEED 100
#include "cocos2d.h"
using namespace cocos2d;
class backgroundlayer:public Layer
{
private:
	float bgheight;
	Size vSize;
	Sprite* bg1;
	Sprite* bg2;
	void update(float t);
public:
	virtual bool init();
	CREATE_FUNC(backgroundlayer);
};
#endif
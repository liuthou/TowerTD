#ifndef __MORETOUCH_H
#define __MORETOUCH_H

#define RELASESKILLMOVELENGH 20
#define MOVEPOINT 100
#define MOVELENGH 5

#include "cocos2d.h"
#include "TouchDir.h"
using namespace cocos2d;

class MoTouch:public Layer
{
private:
	bool _isLeftScreen;
	Vec2 _beginPoint;
public:
	void gameOnHook(Ref * obj);
	void updateOnHook(float t);
	void endOnHook(Ref * obj);
	virtual bool init();
	CREATE_FUNC(MoTouch);
	std::function <void (Driection d)> actionDriection;
	MoTouch():_isLeftScreen(false){}
	~MoTouch();
};
#endif
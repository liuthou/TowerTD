#ifndef __CONTROL_H
#define __CONTROL_H

#include "cocos2d.h"


using namespace cocos2d;

class ControlLayer:public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(ControlLayer);
	Vec2 p;
	EventListenerKeyboard *listenerkeyPad;		//¼üÅÌ
	void onKeyMove(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	void onKeyStop(EventKeyboard::KeyCode keycode, cocos2d::Event *event);

	CC_SYNTHESIZE(bool,isPost,IsPost);

	Vec2 vec;
private:
	void controlRole();

};

#endif // !__CONTROL_H

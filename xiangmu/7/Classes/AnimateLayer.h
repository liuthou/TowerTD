#ifndef __ANIMATELAYER_H
#define __ANIMATELAYER_H
#include "cocos2d.h"
using namespace cocos2d;
class AnimateLayer:public Layer
{
public:
	Sprite * bornAnimate4;
	virtual bool init();
	CREATE_FUNC(AnimateLayer);
	void addBornAnimate();
	void removeSp(float t);
private:

};
#endif // !__ANIMATELAYER_H

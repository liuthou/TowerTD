#ifndef __CONTROLLAYER_H
#define __CONTROLLAYER_H
#include "cocos2d.h"
#include "BaseTank.h"
USING_NS_CC;
class ControlLayer:public Layer
{   BaseTank * tank;
     ControlLayer(){this->tank = nullptr;}
	 ~ControlLayer(){CC_SAFE_RELEASE_NULL(tank);shareControl = nullptr;}
public:
	static ControlLayer * shareControl;
	virtual bool init();
	void bindControlTarget(BaseTank *tank);
	CREATE_FUNC(ControlLayer);
};
#endif // !__CONTROLLAYER_H

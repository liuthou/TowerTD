#ifndef __BOUNDINGLAYER_H_
#define __BOUNDINGLAYER_H_
#include "cocos2d.h"
#include "BaseBlock.h"
#include "BaseTools.h"
USING_NS_CC;

class BoundingLayer : public Layer{
public:
	CREATE_FUNC(BoundingLayer);
protected:
	//发送通知，key为道具或者障碍的名字
	void notification(BaseSprite * sprite);
	virtual bool init();
private:
	void addPhysicsEvent();
};
#endif // !__BOUNDINGLAYER_H_

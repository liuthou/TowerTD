#ifndef __FISHLAYER_H
#define __FISHLAYER_H

#include "cocos2d.h"
USING_NS_CC;

class FishLayer :public Layer
{
public:	

	virtual bool init();
	CREATE_FUNC(FishLayer);

protected:
	Sprite3D* _sprite;
	Animate3D* _swim;
	Animate3D* _hurt;
};

#endif
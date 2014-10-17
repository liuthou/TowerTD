#pragma once

#include "AppMacro.h"

class MainPlane;

/*
	抽象飞行基类，敌机和道具的基类
*/
class BaseAirObject : public Sprite{
public:
	virtual void effectWhileCollision(Ref* obj) = 0;
};

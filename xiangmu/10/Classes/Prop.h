#pragma once

#include "AppMacro.h"
#include "BaseAirObject.h"

// class BaseAirObject; 继承的时候不能使用这种方式

class Prop :public BaseAirObject{
protected:
	virtual bool init();
public:
	CREATE_FUNC(Prop);

	virtual void effectWhileCollision(Ref *obj);
};
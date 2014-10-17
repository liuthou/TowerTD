#include "BinderLayer.h"
#include "BinderRoleStone.h"

bool BinderLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	BinderRoleStone * sp = BinderRoleStone::create();
	this->addChild(sp);
	return true;
}
#include "DelegetLayer.h"
#include "uiRiskLayer.h"

bool DelegetLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//³õÊ¼UI²ã
	auto risklayer = uiRiskLayer::create();
	this->addChild(risklayer);
	return true;
}
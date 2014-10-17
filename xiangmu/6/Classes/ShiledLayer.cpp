#include "ShiledLayer.h"
#include "SystemMarcoUtil.h"
bool ShiledLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	auto listen = EventListenerTouchOneByOne::create();
	listen->onTouchBegan = [=](Touch * touch , Event * event){
		return true;
	};
	listen->setSwallowTouches(true);
	auto dis =  Director::getInstance()->getEventDispatcher();
	dis->addEventListenerWithSceneGraphPriority(listen,this);
	return true;
}

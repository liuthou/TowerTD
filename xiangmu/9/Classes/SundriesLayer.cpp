#include "SundriesLayer.h"

bool SundriesLayer::init()
{
    if(!Layer::init())
	{
	   return true;
	}
	MenuItemFont *menuItem = MenuItemFont::create("start",[=](Ref * obj){
		auto onHook = __NotificationCenter::getInstance();
		onHook->postNotification("staicOnHook");
	});
	MenuItemFont *menuItem1 = MenuItemFont::create("end",[=](Ref * obj){
		auto endOnHook = __NotificationCenter::getInstance();
		endOnHook->postNotification("endOnHook");
	});
	Menu * men = Menu::create(menuItem, menuItem1, NULL);
	men->alignItemsVertically();
	men->setColor(Color3B::BLACK);
	men->setPositionY(550);
	this->addChild(men);
	return true;
}

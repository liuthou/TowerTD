#include "AboutLayer.h"

bool AboutLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size vSize = Director::getInstance()->getVisibleSize();
	auto bg = Sprite::create("we.png");
	bg->setPosition(Vec2(4*vSize.width / 9, vSize.height / 2));
	bg->setScale(0.5f);
	this->addChild(bg);
	auto item1 = MenuItemImage::create("c1.png", "c2.png", [=](Ref *sender){
		this->removeAllChildrenWithCleanup(true);
	});
	auto menu = Menu::create(item1, NULL);
	menu->setPosition(Vec2(7.2 * vSize.width / 9, 5 * vSize.height / 6));
	this->addChild(menu);
	return true;
}
#include "storeSelectLayer.h"
#include "ShiledLayer.h"
#include "SystemMarcoUtil.h"
void StoreSelectLayer::addShiledLayer()
{
	ShiledLayer * shiledLayer = ShiledLayer::create();
	this->addChild(shiledLayer);
}
StoreSelectLayer * StoreSelectLayer::create(int money)
{
	auto storeSelectLayer = new StoreSelectLayer();
	if (storeSelectLayer && storeSelectLayer->init(money))
	{
		storeSelectLayer->autorelease();
        return storeSelectLayer;
	}
	else
	{
		CC_SAFE_DELETE(storeSelectLayer);
		return nullptr;
	}
}
bool StoreSelectLayer::init(int money)
{
	if (!Layer::init())
	{
		return false;
	}
	addShiledLayer();
	willReduceMoney = money;
	Sprite * bg_sprite = Sprite::create("Select.png");
	bg_sprite->setPosition(Vec2(GET_WINDOWS_SIZE/2));
	this->addChild(bg_sprite);
	auto trueItem = MenuItemSprite::create(Sprite::create("true.png"), Sprite::create("true.png"),CC_CALLBACK_1(StoreSelectLayer::sendInform,this));
	auto falseItem = MenuItemSprite::create(Sprite::create("False.png"),Sprite::create("False.png"),CC_CALLBACK_1(StoreSelectLayer::removeSelfLayer,this));
	Menu * selectMenu = Menu::create(trueItem, falseItem,NULL);
	selectMenu->alignItemsHorizontallyWithPadding(100);
	selectMenu->setPosition(Vec2(bg_sprite->getContentSize().width/2, bg_sprite->getContentSize().height/6));
	bg_sprite->addChild(selectMenu);
	return true;
}

void StoreSelectLayer::sendInform(Ref * sender)
{
	//send reduce money
	log("$$$$$$$$$$$$$$$$$$$%d",willReduceMoney);
	__NotificationCenter::getInstance()->postNotification("ReduceMoney",reinterpret_cast<Ref*>(&willReduceMoney));	
}

void StoreSelectLayer::removeSelfLayer(Ref * sender)
{
	this->removeAllChildrenWithCleanup(true);
}
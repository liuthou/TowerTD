#include "MenuItemLayer.h"
#include "SystemMarcoUtil.h"
#include "TemLayer.h"
#include "PersonLayer.h"
#include "EquipLayer.h"
#include "ShiledLayer.h"

bool MenuItemLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Sprite * storeBackGround = Sprite::create("storeBack.png");
	storeBackGround->setPosition(Vec2(GET_WINDOWS_SIZE/2));
	this->addChild(storeBackGround);
	Sprite * tile = Sprite::create("title3.png");
	tile->setPosition(Vec2(GET_WINDOWS_SIZE.width/2,GET_WINDOWS_SIZE.height - tile->getContentSize().height/2));
	this->addChild(tile);
	
	PersonLayer * personLayer = PersonLayer::create();
	TemLayer * temLayer = TemLayer::create();
	EquipLayer * equipLayer = EquipLayer::create();

	layerVector = LayerMultiplex::create(personLayer,temLayer,equipLayer,NULL);
	this->addChild(layerVector);

	return true;
}

void MenuItemLayer::onEnter()
{
	Layer::onEnter();
	addMenu();
}

void MenuItemLayer::addMenu()
{
	auto backItem = MenuItemImage::create("titler.png","titler.png",CC_CALLBACK_1(MenuItemLayer::onCallback,this));

	auto personItemOne = MenuItemImage::create("PeosonItem3.png", "PeosonItem3.png");
	auto personItemSecond = MenuItemImage::create("PeosonItem3.png", "PeosonItem3.png");
	auto personToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuItemLayer::addPersonLayer,this), personItemOne, personItemSecond, NULL);
	
	auto temItemOne = MenuItemImage::create("TemItemt.png", "TemItemt.png");
	auto temItemSecond = MenuItemImage::create("TemItemt.png", "TemItemt.png");
	auto temToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuItemLayer::addTemLayer,this), temItemOne, temItemSecond, NULL);
	
	auto equipItemOne = MenuItemImage::create("ZhuangBeiZ.png", "ZhuangBeiZ.png");
	auto equipItemSecond = MenuItemImage::create("ZhuangBeiZ.png", "ZhuangBeiZ.png");
	auto equipToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuItemLayer::addEquipLayer,this), equipItemOne, equipItemSecond, NULL);
	
	personToggle->setPosition(Vec2(220,890));

	temToggle->setPosition(Vec2(380,890));

	equipToggle->setPosition(Vec2(550,890));

	Menu * menu = Menu::create(backItem, personToggle, temToggle, equipToggle, NULL);
	menu->setPosition(Vec2(GET_WINDOWS_SIZE.width/2,GET_WINDOWS_SIZE.height-backItem->getContentSize().height/2));
	menu->alignItemsHorizontallyWithPadding(45);
	this->addChild(menu);
}


void MenuItemLayer::onCallback(Ref * sender)
{
	//return setting page
    Director::getInstance()->popScene();
}


void MenuItemLayer::addPersonLayer(Ref * sender)
{
	//add PersonLayer
	
	layerVector->switchTo(0);
}


void MenuItemLayer::addTemLayer(Ref * sender)
{
	//add TemLayer
	
		layerVector->switchTo(1);
}


void MenuItemLayer::addEquipLayer(Ref * sender)
{
	//add EquipLayer

		layerVector->switchTo(2);
}

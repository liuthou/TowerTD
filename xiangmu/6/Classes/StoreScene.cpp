#include "StoreScene.h"
#include "MenuItemLayer.h"
bool StoreScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	addMenuItemLayer();
	return true;
}

void StoreScene::addMenuItemLayer()
{
	MenuItemLayer * menuItemLayer = MenuItemLayer::create();
	this->addChild(menuItemLayer);
}
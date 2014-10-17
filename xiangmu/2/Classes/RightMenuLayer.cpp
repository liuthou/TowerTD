
#include "VisibileSize.h"
#include "RightMenuLayer.h"
#include "RightMenuLayerLayer.h"

bool RightMenuLayer::init(){
	if (!Layer::init()){
		return false;
	}


	RightMenuLayerLayer * rightmenulayer_layer = RightMenuLayerLayer::create();
	rightmenulayer_layer->setVisible(false);
	this->addChild(rightmenulayer_layer);

	//menu
	MenuItemImage *menu_image_down = MenuItemImage::create("main_down_button.png", "main_down_button.png");
	menu_image_down->setName("down");

	MenuItemImage *menu_image_up = MenuItemImage::create("main_up_button.png", "main_up_button.png");
	menu_image_up->setName("up");

	MenuItemToggle * menuToggle = MenuItemToggle::createWithCallback([=](Ref *sender){
		MenuItemToggle * to = dynamic_cast<MenuItemToggle *>(sender);
		MenuItemImage *im = dynamic_cast<MenuItemImage *>(to->getSelectedItem());
		std::string name = im->getName();
		if (name == "up"){
			rightmenulayer_layer->setVisible(false);
		}
		else
		{
			rightmenulayer_layer->setVisible(true);
		}
	}, menu_image_up, menu_image_down, NULL);

	Menu * menu = Menu::create(menuToggle, NULL);
	menu->setPosition(Vec2(vSize.width - menu_image_up->getContentSize().width / 2, vSize.height - menu_image_up->getContentSize().height / 2));
	this->addChild(menu);

	rightmenulayer_layer->setPosition(Vec2(vSize.width / 2 - menu_image_up->getContentSize().width / 2, vSize.height / 2 - rightmenulayer_layer->getContentSize().height / 2 + menu_image_up->getContentSize().height / 2));
	return true;
}
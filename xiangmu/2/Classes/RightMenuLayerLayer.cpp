
#include "RightMenuLayerLayer.h"
#include "HeroInformationScene.h"

bool RightMenuLayerLayer::init(){
	if (!Layer::init()){
		return false;
	}


	MenuItemImage * image_hero = MenuItemImage::create("main_hero_button.jpg", "main_hero_button_shade.jpg", CC_CALLBACK_1(RightMenuLayerLayer::callback,this));

	MenuItemImage * image_package = MenuItemImage::create("main_package_button.jpg", "main_package_button_shade.jpg");

	MenuItemImage * image_fragment = MenuItemImage::create("main_fragment_button.jpg", "main_fragment_button_shade.jpg");

	MenuItemImage * image_task = MenuItemImage::create("main_task_button.jpg", "main_task_button_shade.jpg");

	MenuItemImage * image_menu = MenuItemImage::create("main_menu_todolist_1.jpg", "main_menu_todolist_2.jpg");

	Menu *menu_all = Menu::create(image_hero, image_package, image_fragment, image_task, image_menu, nullptr);
	menu_all->alignItemsVerticallyWithPadding(0);
	this->addChild(menu_all);
	return true;
}
void RightMenuLayerLayer::callback(Ref *sender)
{
	auto scene = HeroInformationScene::create();
	Director::getInstance()->pushScene(scene);
}

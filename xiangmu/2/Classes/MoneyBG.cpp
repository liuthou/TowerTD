#include "MoneyBG.h"
#include "VisibileSize.h"

Scene * MoneyBG::createScene(){
	auto scene = Scene::create();
	auto layer = MoneyBG::create();
	scene->addChild(layer);
	return scene;
}

bool MoneyBG::init(){
	if (!Layer::init()){
		return false;
	}
	this->setSwallowsTouches(true);
	auto dis = Director::getInstance()->getEventDispatcher();
	auto listen = EventListenerTouchOneByOne::create();
	listen->onTouchBegan = [=](Touch * t, Event * e){
		return true;
	};
	dis->addEventListenerWithSceneGraphPriority(listen, this);

	BG = Sprite::create("ChangeAttackBG.png");
	BG->setPosition(vSize / 2);
	BG->setScale(0.5, 0.5);
	this->addChild(BG);

	bg = Sprite::create("art_mas.png");
	bg->setPosition(vSize.width / 2, vSize.height / 3 * 2);
	bg->setScale(2);
	this->addChild(bg);

	auto menuitem = MenuItemImage::create("herodetail-detail-close-.png", "herodetail-detail-close-.png", CC_CALLBACK_1(MoneyBG::back, this));
	menuItem = Menu::create(menuitem, NULL);
	menuItem->setPosition(vSize.width / 2 + 20, vSize.height / 3 * 2 - 10);
	menuItem->setScale(0.6);
	this->addChild(menuItem);
	return true;
}
void MoneyBG::back(Ref * sender){
	Director::getInstance()->popScene();
// 	bg->setOpacity(0);
// 	menuItem->setOpacity(0);
// 	BG->setOpacity(0);
}
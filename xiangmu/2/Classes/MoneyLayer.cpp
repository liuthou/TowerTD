#include "MoneyLayer.h"
#include "VisibileSize.h"
#include "MoneyBG.h"
#include "RoleAmrature.h"
Scene * MoneyLayer::createScene(){
	auto scene = Scene::create();
	auto layer = MoneyLayer::create();
	scene->addChild(layer);
	return scene;
}
bool MoneyLayer::init(){
	if (!Layer::init()){
		return false;
	}
	this->scheduleUpdate();
	auto moneyBG = Sprite::create("herodetail-detail.png");
	moneyBG->setPosition(vSize.width / 3, (vSize.height / 15) * 14);
	moneyBG->setScale(1.4, 0.7);
	moneyBG->setOpacity(160);
	this->addChild(moneyBG);

	auto diamondBG = Sprite::create("herodetail-detail.png");
	diamondBG->setPosition(vSize.width / 3 * 2, (vSize.height / 15) * 14);
	diamondBG->setScale(1.4, 0.7);
	diamondBG->setOpacity(160);
	this->addChild(diamondBG);

	auto money = Sprite::create("task_gold_icon_.png");
	money->setPosition(moneyBG->getPositionX() + 120, moneyBG->getPositionY());
	money->setScale(0.7, 0.7);
	this->addChild(money);

	auto diamond = Sprite::create("task_rmb_icon_.png");
	diamond->setPosition(diamondBG->getPositionX() + 120, diamondBG->getPositionY());
	diamond->setScale(0.7, 0.7);
	this->addChild(diamond);

	auto item = MenuItemImage::create("main_status_plus_icon_.png", "main_status_plus_icon_.png", CC_CALLBACK_1(MoneyLayer::money, this));
	item->setScale(0.7, 0.7);
	auto menu = Menu::create(item, NULL);
	menu->setPosition(moneyBG->getPositionX() - 120, moneyBG->getPositionY());
	this->addChild(menu);

	auto addd = Sprite::create("main_status_plus_icon_.png");
	addd->setPosition(diamondBG->getPositionX() - 120, diamondBG->getPositionY());
	addd->setScale(0.7, 0.7);
	this->addChild(addd);

	auto strMoney = StringUtils::format("%d", RoleAmrature::getInstance()->getRoleMoney());
	auto label = Label::create(strMoney, "Arial", 30);
	label->setName("label");
	label->setPosition(moneyBG->getPositionX() , moneyBG->getPositionY());
	this->addChild(label);

	return true;
}

void MoneyLayer::money(Ref * sender){
	auto scene = MoneyBG::createScene();
	Director::getInstance()->pushScene(scene);
//	this->addChild(moneybg);
}

void MoneyLayer::update(float t)
{
	auto label = (Label *)this->getChildByName("label");
	auto str = StringUtils::format("%d", RoleAmrature::getInstance()->getRoleMoney());
	label->setString(str);
}

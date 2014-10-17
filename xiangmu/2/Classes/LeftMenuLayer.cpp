
#include "LeftMenuLayer.h"
#include "VisibileSize.h"
#include "MainRoleAmrature.h"
#include "RoleAmrature.h"

bool LeftMenuLayer::init(){
	if (!Layer::init()) {
		return false;
	}
	this->scheduleUpdate();
	auto playerMenu = MenuItemImage::create("Player_Menu_Left.png", "Player_Menu_Left.png", CC_CALLBACK_1(LeftMenuLayer::playerInformation, this));
	auto level = RoleAmrature::getInstance()->getRoleLevel();
	auto strLevel = StringUtils::format("%d", level);
	auto levelItem = MenuItemFont::create(strLevel);
	levelItem->setName("level");
	levelItem->setPosition(playerMenu->getContentSize().width / 5, -playerMenu->getContentSize().height / 10);
	auto leftMenu = Menu::create(playerMenu, levelItem, NULL);
	leftMenu->setPosition(Vec2(playerMenu->getContentSize().width / 2,
		vSize.height - playerMenu->getContentSize().height / 2));
	leftMenu->setName("menu");
	this->addChild(leftMenu);
	return true;
}
void LeftMenuLayer::update(float t)
{
	auto menu = (Menu *)this->getChildByName("menu");
	auto menuItem = (MenuItemFont *)menu->getChildByName("level");
	auto label = (Label *)menuItem->getLabel();
	auto str =StringUtils::format( "%d",RoleAmrature::getInstance()->getRoleExp()/1000 + 1);
	RoleAmrature::getInstance()->setRoleLevel(RoleAmrature::getInstance()->getRoleExp() / 100 + 1);
	label->setString(str);
}


void LeftMenuLayer::playerInformation(Ref * sender){

	auto scene = MainRoleAmratue::createScene();
	Director::getInstance()->pushScene(scene);
}

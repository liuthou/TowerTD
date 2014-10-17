#include "MainRoleAmrature.h"
#include "VisibileSize.h"
#include "RoleAmrature.h"
#include "tinyxml2/tinyxml2.h"
#include "RoleAmrature.h"

using namespace tinyxml2;

Scene * MainRoleAmratue::createScene()
{
	auto scene = Scene::create();
	auto layer = MainRoleAmratue::create();
	scene->addChild(layer);
	return scene;
}
bool MainRoleAmratue::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->scheduleUpdate();
		auto sprite = Sprite::create("24.jpg");
		this->addChild(sprite);
		sprite->setScaleX(vSize.width / sprite->getContentSize().width);
		sprite->setScaleY(vSize.height / sprite->getContentSize().height);
		sprite->setPosition(vSize / 2);
		int lv = RoleAmrature::getInstance()->getRoleLevel();
		int  Exp = RoleAmrature::getInstance()->getRoleExp();
		int  Money= RoleAmrature::getInstance()->getRoleMoney();
		auto strLv = StringUtils::format("LV:%d",lv );
		auto strExp = StringUtils::format("EXP:%d",Exp );
		auto strMoney = StringUtils::format("Money:%d",Money);
		auto menuItemName = MenuItemFont::create("Name: Never More");
		auto menuItemLevel = MenuItemFont::create(strLv);
		menuItemLevel->setName("menuItemLevel");
		auto menuItemExp = MenuItemFont::create(strExp);
		menuItemExp->setName("menuItemExp");
		auto menuItemMoney = MenuItemFont::create(strMoney);
		menuItemMoney->setName("menuItemMoney");
		auto menu = Menu::create(menuItemName, menuItemLevel, menuItemExp, menuItemMoney,NULL);
		menu->setName("menu");
		this->addChild(menu);
		menu->setPosition(Vec2(vSize / 5));
		menu->alignItemsVertically();
		auto returnItem = MenuItemImage::create("common_tips_button_close_.png", "common_tips_button_close_.png", CC_CALLBACK_1(MainRoleAmratue::callBack, this));
		auto returnMenu = Menu::create(returnItem, NULL);
		float rmX = vSize.width - returnItem->getContentSize().width / 2;
		float rmY = vSize.height - returnItem->getContentSize().height / 2;
		returnMenu->setPosition(Vec2(rmX, rmY));
		auto menuItemFont = MenuItemFont::create("Save Game", CC_CALLBACK_1(MainRoleAmratue::callBackSaveGame,this));		this->addChild(returnMenu);		auto itemFontSaveGame = MenuItemFont::create("Save Game", CC_CALLBACK_1(MainRoleAmratue::callBackSaveGame, this));
		auto itemEndGame = MenuItemFont::create("End Game", CC_CALLBACK_1(MainRoleAmratue::callBackEndGame, this));
		auto menu_endGame = Menu::create(itemEndGame, itemFontSaveGame, NULL);
		itemFontSaveGame->setPosition(Vec2(vSize.width * 4 / 5,vSize.height * 2 / 5));
		itemEndGame->setPosition(Vec2(vSize.width * 4 / 5, vSize.height / 5));
		this->addChild(menu_endGame);
		menu_endGame->setPosition(Vec2(0, 0));
		return true;
}
void MainRoleAmratue::callBack(Ref * sender)
{
	Director::getInstance()->popScene();
}
void MainRoleAmratue::callBackSaveGame(Ref * sender)
{
	auto strFileName = FileUtils::getInstance()->getStringFromFile("MainRole.xml");
	tinyxml2::XMLDocument doc;
	doc.Parse(strFileName.c_str());
	auto rootElement = doc.RootElement();
	auto element = rootElement->FirstChildElement();
	element->SetAttribute("LEVEL", RoleAmrature::getInstance()->getRoleExp()/1000+1);
	element->SetAttribute("EXP", RoleAmrature::getInstance()->getRoleExp());
	element->SetAttribute("MONEY", RoleAmrature::getInstance()->getRoleMoney());
	doc.SaveFile(strFileName.c_str());
	
}
void MainRoleAmratue::callBackEndGame(Ref * sender)
{
	Director::getInstance()->end();
}
void MainRoleAmratue::update(float t)
{
	auto menu = (Menu *)this->getChildByName("menu");
	auto menuItemLevel = (MenuItemFont *)menu->getChildByName("menuItemLevel");
	auto menuItemExp = (MenuItemFont *)menu->getChildByName("menuItemExp");
	auto menuItemMoney = (MenuItemFont *)menu->getChildByName("menuItemMoney");
	auto labelLevel = (Label *)menuItemLevel->getLabel();
	auto labelExp = (Label *)menuItemExp->getLabel();
	auto labelMoney = (Label *)menuItemMoney->getLabel();
	auto strLevel = StringUtils::format("Level:%d", RoleAmrature::getInstance()->getRoleExp()/1000+1);
	auto strExp = StringUtils::format("EXP:%d", RoleAmrature::getInstance()->getRoleExp());
	auto strMoney = StringUtils::format("Money:%d", RoleAmrature::getInstance()->getRoleMoney());
	labelLevel->setString(strLevel);
	labelExp->setString(strExp);
	labelMoney->setString(strMoney);
}

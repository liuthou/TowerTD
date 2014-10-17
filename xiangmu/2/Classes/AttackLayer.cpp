
#include "AttackLayer.h"
#include "VectorItemImage.h"
#include "GameAttackScene.h"
#include "Bullets.h"
#include "SelectRole.h"
#include "EnemyLayer.h"
#include "ChangeAttackScene.h"
#include "VectorItemImage.h"
#include "choseInformation.h"
#include "tinyxml2/tinyxml2.h"
#include "RoleAmrature.h"
#include "SFRole.h"
#include "NecRole.h"
#include "HpLoadingbar.h"
#include "SimpleAudioEngine.h"
#include "SelectRole.h"

bool AttackLayer::init(){
	if (!Layer::init()) {
		return false;
	}
	bgX = Director::getInstance()->getVisibleSize().width;
	bgY = Director::getInstance()->getVisibleSize().height;

	//创建背景
	bg = Sprite::create(choseInformation::getInstence()->getImageName());
	bg->setPosition(Vec2(bgX / 2, bgY / 2));
	bg->setScale(1.109, 1.04);
	addChild(bg);


	//创建英雄按钮的背景
	herowindow = Sprite::create("Attack_Hero_Window.png");
	herowindow->setPosition(bgX / 2, herowindow->getContentSize().height / 2);
	addChild(herowindow);



	//导入英雄
	addHeroWindow();

	//遮罩层
	shield = Sprite::create("Attack_Hero_Window.png");
	shield->setScale(1.37, 4.15);
	shield->setPosition(bgX / 2, bgY / 2);
	shield->setVisible(false);
	this->addChild(shield);


	//暂停按钮
	auto stopItem = MenuItemImage::create("pausebt.png", "pausebtn-disable.png", CC_CALLBACK_1(AttackLayer::stopLayer, this));
	auto stopMenu = Menu::create(stopItem, NULL);
	stopMenu->setName("stop");
	stopItem->setName("name");
	
	float smX = stopItem->getContentSize().width;
	float smY = bgY - stopItem->getContentSize().height / 2;
	stopMenu->setPosition(Vec2(smX, smY));
	addChild(stopMenu);

	//通往下一层的按钮
	nextitem = MenuItemImage::create("NextMapMenuItem.png", "NextMapMenuItem.png", CC_CALLBACK_1(AttackLayer::nextMap, this));
	nextitem->setVisible(false);
	auto nextMenu = Menu::create(nextitem, NULL);
	float nmX = bgX - nextitem->getContentSize().width;
	float nmY = bgY / 2;
	nextMenu->setPosition(Vec2(nmX, nmY));
	addChild(nextMenu);
	auto move_a = MoveBy::create(0.5, Vec2(40, 0));
	auto move_b = MoveTo::create(0.5, nextMenu->getPosition());
	auto seq = Sequence::create(move_a, move_b, NULL);
	nextMenu->runAction(RepeatForever::create(seq));

	//自动战斗按钮
	auto automaticItem = MenuItemImage::create("Automatic_a.png", "Automatic_b.png",CC_CALLBACK_1(AttackLayer::automaticAttack,this));
	float amX = herowindow->getPosition().x + herowindow->getContentSize().width / 2 + automaticItem->getContentSize().width / 2;
	float amY = herowindow->getPosition().y;
	automaticItem->setPosition(Vec2(amX, amY));
	auto menuMaticItem = Menu::create(automaticItem,nullptr);
	menuMaticItem->setPosition(0,0);
	automaticItem->setName("automatic");
	menuMaticItem->setName("menuMaticItem");
	this->addChild(menuMaticItem);
	return true;
}

void AttackLayer::addHeroWindow(){


	//创建英雄按钮
	auto menu = Menu::create();
	float mx = herowindow->getPosition().x - herowindow->getContentSize().width / 2;
	float my = herowindow->getPosition().y + herowindow->getContentSize().height / 2;
	menu->setPosition(Vec2(mx, my));
	
	auto itemvector = VectorItemImage::getInstance()->getItemImageVector();
	log("%d", itemvector.size());
// 	for (int j = 0; j <  itemvector.size(); j++)
// 	{
// 		auto menuitemimage = MenuItemImage::create("imageSF.png","imageSF.png", CC_CALLBACK_1(AttackLayer::menuCallback,this));
// 	//	menuitemimage->setVisible(;
// 		menuitemimage->setPosition(Vec2(134 * j + 62, -72));
// 		menu->addChild(menuitemimage,10);
// 	}
	for (int i = 0; i < itemvector.size(); i++) {
		auto  menuitem = itemvector.at(i);
		menuitem->setTag(i);
		menuitem->setCallback(CC_CALLBACK_1(AttackLayer::menuCallback,this));
		menuitem->setPosition(Vec2(134 * i + 62, -72));
		menu->addChild(menuitem);
		
	}
	addChild(menu);
}

void AttackLayer::stopLayer(Ref * sender){
	shield->setVisible(true);
	auto menuItem = (MenuItem *)sender;
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	menuItem->setEnabled(false);
	log("%s",menuItem->getName().c_str());
	auto EndGame = MenuItemImage::create("backbt.png", "backbtn-disable.png", CC_CALLBACK_1(AttackLayer::popGameScene,this));
	EndGame->setName("EndGame");
	EndGame->setVisible(true);
	auto EndItem = MenuItemImage::create("EndAttack_a.png", "EndAttack_b.png", CC_CALLBACK_1(AttackLayer::EndMenu, this));
	auto menu = Menu::create(EndItem, EndGame, NULL);
	menu->setName("Menu");
	menu->setPosition(bgX / 2, bgY / 2);
	menu->alignItemsVertically();
	addChild(menu);
	auto maticmenu = (Menu* )this->getChildByName("menuMaticItem");
	auto maticItem = (MenuItemImage* )maticmenu->getChildByName("automatic");
	maticItem->setEnabled(false);
	Director::getInstance()->pause();
}

void AttackLayer::EndMenu(Ref * sender){
	shield->setVisible(false);
	auto maticmenu = (Menu*)this->getChildByName("menuMaticItem");
	auto maticItem = (MenuItemImage*)maticmenu->getChildByName("automatic");
	maticItem->setEnabled(true);
	auto menu1 = (Menu*)this->getChildByName("Menu");
	auto menuItem1 = (MenuItemImage*)menu1->getChildByName("EndGame");
	menuItem1->setVisible(false);
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	auto menu = (Menu* )this->getChildByName("stop");
	auto menuitem = (MenuItem*)menu->getChildByName("name");
	menuitem->setEnabled(true);
	MenuItemImage * item = (MenuItemImage *)sender;
	auto menuP = (Menu* )item->getParent();
	menuP->setVisible(false);
	item->setVisible(false);
	Director::getInstance()->resume();
}

void AttackLayer::nextMap(Ref * sender){
	Bullets::getInstence()->deleteEnemyBulletsAll();
	Bullets::getInstence()->deleteRoleBulletsAll();
	SelectRole::getInstence()->EnemyClearaAll();
	GameAttackScene *scene = dynamic_cast<GameAttackScene *>(Director::getInstance()->getRunningScene());
	EnemyLayer *enemyLayer = dynamic_cast<EnemyLayer *>(scene->getEnemyLayer());
	std::string imageName = enemyLayer->ReadEnemyXml();
	if(imageName == "over"){
		auto strFileName = FileUtils::getInstance()->getStringFromFile("MainRole.xml");
		tinyxml2::XMLDocument doc;
		doc.Parse(strFileName.c_str());
		auto rootElement = doc.RootElement();
		auto element = rootElement->FirstChildElement();
		element->SetAttribute("LEVEL", RoleAmrature::getInstance()->getRoleExp() / 1000 + 1);
		element->SetAttribute("EXP", RoleAmrature::getInstance()->getRoleExp());
		element->SetAttribute("MONEY", RoleAmrature::getInstance()->getRoleMoney());
		doc.SaveFile(strFileName.c_str());
		Bullets::getInstence()->deleteEnemyBulletsAll();
		Bullets::getInstence()->deleteRoleBulletsAll();
		SelectRole::getInstence()->EnemyClearaAll();
		SelectRole::getInstence()->RoleClearAll();
		VectorItemImage::getInstance()->reset();
		ChangeAttackScene *scene = ChangeAttackScene::create();
		Director::getInstance()->replaceScene(scene);
		return;
	}
	setBg(imageName);
	for(int i = 0; i < SelectRole::getInstence()->getRoleArmatures().size();i++){
		auto role = SelectRole::getInstence()->getRoleArmatures().at(i);
		role->setPositionX(-50 - i*-50);
		role->setArmaturestatic(moveStatic);
	}
	nextitem->setVisible(false);
}

void AttackLayer::automaticAttack(Ref * sender){
	//__NotificationCenter::getInstance()->postNotification("skill");

}
void AttackLayer::setNextMapVisable(bool isVisible){
	for(int i = 0; i < SelectRole::getInstence()->getRoleArmatures().size();i++){
		auto role = SelectRole::getInstence()->getRoleArmatures().at(i);
		role->setArmaturestatic(noStatic);
	}
	nextitem->setVisible(isVisible);
}
void AttackLayer::setBg(std::string TexName){
	Image *image = new Image();
	image->initWithImageFile(TexName);
	Texture2D *tex = new Texture2D();
	tex->initWithImage(image);
	bg->setTexture(tex);
}
void AttackLayer::menuCallback(Ref * sender)
{
	auto menuItemImage = (MenuItemImage *)sender;
	auto i =menuItemImage->getTag();
	
	if (i == 0)
	{
		auto sf = (SFRole *)SelectRole::getInstence()->getRoleArmatures().at(0);
		log("%d",sf->getMp());
		if (sf->getMp() >= 99)
		{
			__NotificationCenter::getInstance()->postNotification("skill");
			auto layer = (HpLoadingbar *)SelectRole::getInstence()->getHpLayer().at(0);
			layer->loadingBarMp->setPercent(1);
            sf->setMp(0);
            log("%d",sf->getMp());
    
		}
	}else if (i == 1)
	{
		auto sf = (NECRole *)SelectRole::getInstence()->getRoleArmatures().at(1);
		if (sf->getMp() >= 99)
		{
			__NotificationCenter::getInstance()->postNotification("skill");
			auto layer = (HpLoadingbar *)SelectRole::getInstence()->getHpLayer().at(1);
			layer->loadingBarMp->setPercent(1);
		}
	}
	

}
void AttackLayer::popGameScene(Ref* sender)
{
	Director::getInstance()->resume();
	SelectRole::getInstence()->RoleClearAll();
	VectorItemImage::getInstance()->reset();
	Director::getInstance()->popToRootScene();

}

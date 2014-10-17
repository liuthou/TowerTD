#include "GameSceneOver.h"
#include "VisibileSize.h"
#include "VectorItemImage.h"
#include "SelectRole.h"
#include "Bullets.h"

bool GameOverScene::init(){
	if (!Scene::init()){
		return false;
	}

	auto bg = Sprite::create("ChangeAttackBG.png");
	bg->setPosition(vSize / 2);
	bg->setScale(vSize.width / bg->getContentSize().width, vSize.height / bg->getContentSize().height);
	this->addChild(bg);

	auto sf = Sprite::create("SF_Image.png");
	sf->setPosition(vSize.width / 2, vSize.height / 2 + 150);
	sf->setScale(2);
	this->addChild(sf);

	auto reborn = Sprite::create("act_icon_difficulty_3.png");
	reborn->setPosition(vSize.width / 3, vSize.height / 2 - 100);
	this->addChild(reborn);

	auto pass = Sprite::create("act_icon_difficulty_4.png");
	pass->setPosition(vSize.width / 2, vSize.height / 2 - 100);
	this->addChild(pass);

	auto die = Sprite::create("act_icon_difficulty_1.png");
	die->setPosition(vSize.width / 3 * 2, vSize.height / 2 - 100);
	this->addChild(die);

	MenuItemFont * item1 = MenuItemFont::create("Reborn", CC_CALLBACK_1(GameOverScene::Reborn, this));
	item1->setPosition(vSize.width / 3, vSize.height / 2 - 180);
	MenuItemFont * item2 = MenuItemFont::create("Pass", CC_CALLBACK_1(GameOverScene::Pass, this));
	item2->setPosition(vSize.width / 2, vSize.height / 2 - 180);
	MenuItemFont * item3 = MenuItemFont::create("Die", CC_CALLBACK_1(GameOverScene::Die, this));
	item3->setPosition(vSize.width / 3 * 2, vSize.height / 2 - 180);
	Menu * menu = Menu::create(item1, item2, item3, NULL);
	menu->setPosition(0, 0);
	this->addChild(menu);

	Sprite * m1 = Sprite::create("task_gold_icon_.png");
	m1->setPosition(vSize.width / 3 - 60, vSize.height / 2 - 220);
	this->addChild(m1);
	Sprite * m2 = Sprite::create("task_gold_icon_.png");
	m2->setPosition(vSize.width / 2 - 70, vSize.height / 2 - 220);
	this->addChild(m2);
	Sprite * m3 = Sprite::create("task_gold_icon_.png");
	m3->setPosition(vSize.width / 3 * 2 - 25, vSize.height / 2 - 220);
	this->addChild(m3);

	Label * label1 = Label::create("5000", "Arial", 40);
	label1->setPosition(vSize.width / 3, vSize.height / 2 - 220);
	this->addChild(label1);
	Label * label2 = Label::create("20000", "Arial", 40);
	label2->setPosition(vSize.width / 2, vSize.height / 2 - 220);
	this->addChild(label2);
	Label * label3 = Label::create("0", "Arial", 40);
	label3->setPosition(vSize.width / 3 * 2, vSize.height / 2 - 220);
	this->addChild(label3);
	return true;
}

void GameOverScene::Reborn(Ref * sender){

}

void GameOverScene::Pass(Ref * sender){

}

void GameOverScene::Die(Ref * sender){
	VectorItemImage::getInstance()->reset();
	Bullets::getInstence()->deleteEnemyBulletsAll();
	SelectRole::getInstence()->EnemyClearaAll();
	Director::getInstance()->popToRootScene();
}

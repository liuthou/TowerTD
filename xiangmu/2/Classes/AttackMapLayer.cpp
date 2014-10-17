
#include "AttackMapLayer.h"
#include "VisibileSize.h"
#include "LevelScene.h"
#include "LevelLayer.h"
#include "choseInformation.h"

bool AttackMapLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	addMapMenu();
	return true;
}

void AttackMapLayer::addMapMenu(){
	//以下全部为设置地图的窗口
	TMXTiledMap * changeMap = TMXTiledMap::create("bakground(1).tmx");
	this->addChild(changeMap);
	float cmX = (vSize.width - changeMap->getContentSize().width) / 2;
	changeMap->setPosition(Vec2(cmX, 0));
	TMXObjectGroup * objectgroup = changeMap->getObjectGroup("object");
	ValueMap valuemap = objectgroup->getObject("object1");
	float x = valuemap.at("x").asFloat();
	float y = valuemap.at("y").asFloat();
	auto menuitem = MenuItemImage::create("stage-9.png", "stage-9.png", CC_CALLBACK_1(AttackMapLayer::changeMap_a_1, this));
	menuitem->setPosition(Vec2(x, y));
	auto menu = Menu::create(menuitem, NULL);
	menu->setPosition(Vec2(cmX, 0));
	//房后闪光
	auto flashBG = Sprite::create("crusade_stage_7_curren.png");
	flashBG->setPosition(Vec2(x , y));
	//动画渐入渐出
	auto flashAnimationOut = FadeOut::create(0.5);
	auto flashAnimationIn = FadeIn::create(0.5);
	auto seqAction = Sequence::create(flashAnimationOut, flashAnimationIn, NULL);
	flashBG->runAction(RepeatForever::create(seqAction));
	addChild(flashBG);


	valuemap = objectgroup->getObject("object2");
	x = valuemap.at("x").asFloat();
	y = valuemap.at("y").asFloat();
	auto  menuitem1 = MenuItemImage::create("stage-19.png", "stage-19.png", CC_CALLBACK_1(AttackMapLayer::changeMap_a_2, this));
	menuitem1->setPosition(Vec2(x, y));
	menu->addChild(menuitem1);

	valuemap = objectgroup->getObject("object3");
	x = valuemap.at("x").asFloat();
	y = valuemap.at("y").asFloat();
	auto  menuitem2 = MenuItemImage::create("stage-23.png", "stage-23.png", CC_CALLBACK_1(AttackMapLayer::changeMap_a_3, this));
	menuitem2->setPosition(Vec2(x, y));
	menu->addChild(menuitem2);

	valuemap = objectgroup->getObject("object4");
	x = valuemap.at("x").asFloat();
	y = valuemap.at("y").asFloat();
	auto  menuitem3 = MenuItemImage::create("stage-25.png", "stage-25.png", CC_CALLBACK_1(AttackMapLayer::changeMap_a_4, this));
	menuitem3->setPosition(Vec2(x, y));
	menu->addChild(menuitem3);


	this->addChild(menu);
}

//点击按钮触发事件
void AttackMapLayer::changeMap_a_1(Ref * sender)
{
	choseInformation::getInstence()->setFileNameXml("OneEnemyOne.xml");
	choseInformation::getInstence()->setImageName("bbg_snow_castle.jpg");
	auto scene = LevelScene::create();
	auto layer = LevelLayer::create("Level_1.png");
	scene->addChild(layer);
	Director::getInstance()->pushScene(scene);

}

void AttackMapLayer::changeMap_a_2(Ref * sender){
	choseInformation::getInstence()->setFileNameXml("twoEnemyOne.xml");
	choseInformation::getInstence()->setImageName("bbg_spring.jpg");
	auto scene = LevelScene::create();
	auto layer = LevelLayer::create("Level_2.png");
	scene->addChild(layer);
	Director::getInstance()->pushScene(scene);

}

void AttackMapLayer::changeMap_a_3(Ref * sender){
	
	choseInformation::getInstence()->setFileNameXml("ThreeEnemyOne.xml");
	choseInformation::getInstence()->setImageName("bbg_spring_sprite.jpg");
	auto scene = LevelScene::create();
	auto layer = LevelLayer::create("Level_3.png");
	scene->addChild(layer);
	Director::getInstance()->pushScene(scene);
}

void AttackMapLayer::changeMap_a_4(Ref * sender){
	choseInformation::getInstence()->setFileNameXml("fourEnemyOne.xml");
	choseInformation::getInstence()->setImageName("bbg_underground_mine.jpg");
	auto scene = LevelScene::create();
	auto layer = LevelLayer::create("Level_4.png");
	scene->addChild(layer);
	Director::getInstance()->pushScene(scene);
}

void AttackMapLayer::changeMap_a_5(Ref * sender){
	auto scene = LevelScene::create();
	auto layer = LevelLayer::create("Level_4.png");
	scene->addChild(layer);
	Director::getInstance()->pushScene(scene);

}

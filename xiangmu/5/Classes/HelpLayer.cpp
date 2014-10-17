#include "HelpLayer.h"
#include "GameData.h"
#include "DataXML.h"
#include "SuspendLayer.h"

bool HelpLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	audioFlag = DataXML::getInstence()->getInitialValue("sound");
	addLayer();
	this->setScale(1.01);
	return true;
}

void HelpLayer::addLayer(){
	auto backGround = Sprite::createWithSpriteFrameName(SCREEN1BACKTUT);
	backGround->setPosition(VISIBLE_SIZE / 2);
	this->addChild(backGround);
	for (int i = 0; i < 3; i++)
	{
		auto bg = Sprite::createWithSpriteFrameName(MOBILEJUMP);
		this->addChild(bg);
		bg->setPosition((VISIBLE_SIZE.width / 4) + i * 200, VISIBLE_SIZE.height / 4);
	}
	auto item = MenuItemImage::create();
	item->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(PLAY_P_1_FILENAME));
	item->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(PLAY_P_2_FILENAME));
	item->setCallback([=](Ref *s){
		EFFECT_MUSIC("click.mp3", audioFlag);
		this->removeAllChildrenWithCleanup(true);
		addLayer2();
	});
	auto menu = Menu::create(item,NULL);
	menu->setPosition(VISIBLE_SIZE.width / 1.2, VISIBLE_SIZE.height / 4);
	this->addChild(menu);
}

void HelpLayer::addLayer2(){
	auto backGround = Sprite::createWithSpriteFrameName(SCREEN2BACKTUT);
	backGround->setPosition(VISIBLE_SIZE / 2);
	this->addChild(backGround);

	auto bgleft = Sprite::createWithSpriteFrameName(MOBILE_LEFT);
	this->addChild(bgleft);

	bgleft->setPosition((VISIBLE_SIZE.width / 3), VISIBLE_SIZE.height / 3.8);
	auto bgright = Sprite::createWithSpriteFrameName(MOBILE_RIGHT);
	bgright->setPosition(VISIBLE_SIZE.width / 2.5 + 200, VISIBLE_SIZE.height / 3.9);
	this->addChild(bgright);

	auto item = MenuItemImage::create();
	item->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(PLAY_P_1_FILENAME));
	item->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(PLAY_P_2_FILENAME));
	item->setCallback([=](Ref *s){
		BACK_GUOUND_MUSIC("chickendance.mp3", audioFlag);
		EFFECT_MUSIC("click.mp3", audioFlag);
		this->removeAllChildrenWithCleanup(true);
		Director::getInstance()->resume();
		//恢复重力感应
		Device::setAccelerometerEnabled(true);
		auto susLayer = dynamic_cast<SuspendLayer *>(this->getParent());
		if (susLayer != nullptr)
		{
			susLayer->removeFromParentAndCleanup(true);
			__NotificationCenter::getInstance()->postNotification("SUSLAYER_REMOVED", this);
		}
	});
	auto menu = Menu::create(item,NULL);
	menu->setPosition(VISIBLE_SIZE.width / 1.2, VISIBLE_SIZE.height / 4);
	this->addChild(menu);
}
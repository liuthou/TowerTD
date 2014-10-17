#include "SuspendLayer.h"
#include "GameData.h"
#include "StartScene.h"
#include "HelpLayer.h"
#include "DataXML.h"

bool SuspendLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	audioFlag = DataXML::getInstence()->getInitialValue("sound");
	//添加黑色背景
	addSprite(BLACK_BACK_FILENAME, Vec2(480, 320), 5);
	//添加暂停背景
	addSprite(ENDBACK_P_FILENAME, Vec2(480, 320), 1);
	//添加暂停LOGO
	addSprite(PAUSEGFX_FILENAME, Vec2(480, 420), 0.8);
	//添加返回主界面按钮
	addMenu(BACK_P_1_FILENAME, BACK_P_2_FILENAME, Vec2(320, 300), false, CC_CALLBACK_1(SuspendLayer::toStartScene, this));
	//添加弹出帮助界面按钮
	addMenu(HOWTOP_1_FILENAME, HOWTOP_2_FILENAME, Vec2(480, 300), false, CC_CALLBACK_1(SuspendLayer::toHelpLayer, this));
	//添加返回游戏界面按钮
	addMenu(PLAY_P_1_FILENAME, PLAY_P_2_FILENAME, Vec2(640, 300), false, CC_CALLBACK_1(SuspendLayer::backToGame, this));

	addTouch();

	this->setScale(0.8);
	return true;
}

void SuspendLayer::addSprite(std::string fileName, Vec2 spritePos, float scaleValue){
	auto sp = Sprite::createWithSpriteFrameName(fileName);
	sp->setPosition(spritePos);
	sp->setScale(scaleValue);
	this->addChild(sp);
}

void SuspendLayer::addMenu(std::string norName, std::string selName, Vec2 menuPos, bool toggleFlag, std::function<void (Ref *)> menuCallback){
	auto normal = SpriteFrameCache::getInstance()->getSpriteFrameByName(norName);
	auto select = SpriteFrameCache::getInstance()->getSpriteFrameByName(selName);
	if (toggleFlag)
	{
		auto itemOn = MenuItemImage::create();
		auto itemOff = MenuItemImage::create();
		itemOn->setNormalSpriteFrame(normal);
		itemOn->setSelectedSpriteFrame(normal);
		itemOff->setNormalSpriteFrame(select);
		itemOff->setSelectedSpriteFrame(select);
		auto toggle = MenuItemToggle::createWithCallback(menuCallback,itemOn,itemOff,NULL);
		auto menuAudio = Menu::create(toggle,NULL);
		menuAudio->setPosition(menuPos);
		this->addChild(menuAudio);
	}else
	{
		auto itemAll = MenuItemImage::create();
		itemAll->setCallback(menuCallback);
		itemAll->setNormalSpriteFrame(normal);
		itemAll->setSelectedSpriteFrame(select);
		auto menu = Menu::create(itemAll,NULL);
		menu->setPosition(menuPos);
		this->addChild(menu);
	}
}

void SuspendLayer::toStartScene(Ref * sender){
	EFFECT_MUSIC("click.mp3", audioFlag);
	Director::getInstance()->resume();
	auto scene = StartScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void SuspendLayer::toHelpLayer(Ref * sender){
	EFFECT_MUSIC("click.mp3", audioFlag);
	auto helpLayer = HelpLayer::create();
	this->addChild(helpLayer);
}

void SuspendLayer::backToGame(Ref * sender){
	BACK_GUOUND_MUSIC("chickendance.mp3", audioFlag);
	EFFECT_MUSIC("click.mp3", audioFlag);
	Director::getInstance()->resume();
	this->removeFromParentAndCleanup(true);
	//发送通知
	__NotificationCenter::getInstance()->postNotification("SUSLAYER_REMOVED", this);
	//恢复重力感应
	Device::setAccelerometerEnabled(true);
}

void SuspendLayer::addTouch() {

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = [](Touch* touch, Event* event){   
		return true;   
	};    
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
}
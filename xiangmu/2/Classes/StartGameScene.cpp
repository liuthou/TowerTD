
#include "GameScene.h"
#include "StartGameScene.h"
#include "VisibileSize.h"
#include "SimpleAudioEngine.h"

Scene * StartGameScene::startSceneCreate()
{
	auto scene = Scene::create();
	auto layer = StartGameScene::create();
	scene->addChild(layer);
	return scene;
}
bool StartGameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	addBackGround();
	addIntoMenu();
	loadingBar();
	return true;
}

void StartGameScene::addBackGround(){
	auto backGround = Sprite::create("24.jpg");
	this->addChild(backGround);
	backGround->setPosition(vSize / 2);
	//缩放尺寸大小
	float scaleX = vSize.width / backGround->getContentSize().width;
	float scaleY = vSize.height / backGround->getContentSize().height;
	backGround->setScale(scaleX, scaleY);
}

void StartGameScene::addIntoMenu(){
	//按钮背景
 //	auto into = Sprite::create("elitetoggle-.png");
// 	into->setPosition(vSize / 2 - Size(0, 200));
// 	into->setScale(1.2, 1.2);
// 	into->setOpacity(170);
// 	this->addChild(into);
	//按钮
	auto item = MenuItemImage::create("elitetoggle-.png", "elitetoggle-.png", CC_CALLBACK_1(StartGameScene::startCallback, this));
	auto menu = Menu::create(item, NULL);
	menu->setPosition(vSize / 2 - Size(0, 200));
	this->addChild(menu);
}

void StartGameScene::startCallback(Ref * sender){

	this->scheduleUpdate();
}
void StartGameScene::loadingBar()
{
	auto sp = Sprite::create("hol.png");
	auto loadingbar = ProgressTimer::create(sp);
	loadingbar->setType(kCCProgressTimerTypeRadial);
	loadingbar->setName("loadingbar");
	loadingbar->setPercentage(0);
	this->addChild(loadingbar);
	loadingbar->setPosition(vSize / 2);
}
void StartGameScene::update(float t)
{
	auto loadingbar = (ProgressTimer * )this->getChildByName("loadingbar");
	loadingbar->setPercentage(loadingbar->getPercentage() + 1);
	if (loadingbar->getPercentage()>=100)
	{
		auto scene = GameScene::create();
		Director::getInstance()->replaceScene(scene);
	}
}
void StartGameScene::onEnter()
{
	Layer::onEnter();
	auto strFlie = FileUtils::getInstance()->fullPathForFilename("battle_bgm.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(strFlie.c_str(), true);
}

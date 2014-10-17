#include "GameOverLayer.h"
#include "GameData.h"
#include "StartScene.h"
#include "GameScene.h"
#include "BackGroundLayer.h"
#include "DataXML.h"

bool GameOverLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	audioFlag = DataXML::getInstence()->getInitialValue("sound");
	//添加黑色背景
	addSprite(BLACK_BACK_FILENAME, Vec2(480, 320), 5);
	//添加游戏结束背景
	addSprite(ENDBACK_P_FILENAME, Vec2(480, 320), 1);
	//添加死亡LOGO
	addSprite(CHICKEN_END_FILENAME, Vec2(480, 420), 0.8);
	//添加返回主界面按钮
	addMenu(BACK_P_1_FILENAME, BACK_P_2_FILENAME, Vec2(320, 300), false, CC_CALLBACK_1(GameOverLayer::toStartScene, this));
	//添加重新开始游戏按钮
	addMenu(REPLAYER_END_1_FILENAME, REPLAYER_END_2_FILENAME, Vec2(640, 300), false, CC_CALLBACK_1(GameOverLayer::onceGame, this));
	//添加空按钮，防止主角死亡后还可以按暂停按钮
	addMenu(NEAR_MISS_COLL_FILENAME, NEAR_MISS_COLL_FILENAME, Vec2(45, 580), false, [](Ref * sender){});
	
	this->setScale(0.8);

	return true;
}

//增加分数显示
void GameOverLayer::addScoreLabel(int curScore, int maxScore){
	//最高分
	Sprite * maxScoreIcon = Sprite::createWithSpriteFrameName(MAX_SCORE_FILENAME);
	maxScoreIcon->setPosition(Vec2(430, 260));
	this->addChild(maxScoreIcon);
	Label * maxScoreLabel = Label::createWithSystemFont(StringUtils::format("%d", maxScore), "Arial", 40);
	maxScoreLabel->setPosition(Vec2(450, 260));
	maxScoreLabel->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(maxScoreLabel);
	//当前分
	Sprite * curScoreIcon = Sprite::createWithSpriteFrameName(TIMER_FILENAME);
	curScoreIcon->setPosition(Vec2(430, 200));
	this->addChild(curScoreIcon);
	Label * curScoreLabel = Label::createWithSystemFont(StringUtils::format("%d", curScore), "Arial", 40);
	curScoreLabel->setPosition(Vec2(450, 200));
	curScoreLabel->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(curScoreLabel);
	//添加新纪录提示
	if (curScore > maxScore)
	{
		addSprite(NEW_RECORD_FILENAME, Vec2(600, 400), 1);
	}
}

//添加精灵方法
void GameOverLayer::addSprite(std::string fileName, Vec2 spritePos, float scaleValue){
	auto sp = Sprite::createWithSpriteFrameName(fileName);
	sp->setPosition(spritePos);
	sp->setScale(scaleValue);
	this->addChild(sp);
}

//添加按钮
void GameOverLayer::addMenu(std::string norName, std::string selName, Vec2 menuPos, bool toggleFlag, std::function<void(Ref *)> menuCallback){
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
		auto toggle = MenuItemToggle::createWithCallback(menuCallback, itemOn, itemOff, NULL);
		auto menuAudio = Menu::create(toggle, NULL);
		menuAudio->setPosition(menuPos);
		this->addChild(menuAudio);
	}
	else
	{
		auto itemAll = MenuItemImage::create();
		itemAll->setCallback(menuCallback);
		itemAll->setNormalSpriteFrame(normal);
		itemAll->setSelectedSpriteFrame(select);
		auto menu = Menu::create(itemAll, NULL);
		menu->setPosition(menuPos);
		this->addChild(menu);
	}
}

//转到开始场景
void GameOverLayer::toStartScene(Ref * sender){
	EFFECT_MUSIC("click.mp3",audioFlag);
	Director::getInstance()->resume();
	auto scene = StartScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

//再玩一次游戏按钮回调
void GameOverLayer::onceGame(Ref * sender){
	EFFECT_MUSIC("click.mp3",audioFlag);
	auto scene = GameScene::create();
	Director::getInstance()->replaceScene(scene);
	Director::getInstance()->resume();
}
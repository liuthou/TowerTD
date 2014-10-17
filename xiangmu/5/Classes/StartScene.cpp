#include "StartScene.h"
#include <SimpleAudioEngine.h>
#include "GameScene.h"
#include "GameData.h"
#include "DataXML.h"
#include "DataXML.h"
#include "AboutLayer.h"

Scene *StartScene::createScene(){
	auto s = Scene::create();
	auto l = StartScene::create();
	s->addChild(l);
	return s;
}

bool StartScene::init(){
	if (!Layer::init()){
		return false;
	}

	audioFlag = DataXML::getInstence()->getInitialValue("sound");
	BACK_GUOUND_MUSIC("ambience.mp3", audioFlag);
	//背景图BackGround
	addSprite(backGround, MAIN_BACK_FILENAME, Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	//游戏Logo Gamelogo 
	addSprite(gameLogo, GAME_LOGO_FILENAME, Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 1.4f));
	//提示 Prompt
	addSprite(prompt, INSTRUCTIONS_FILENAME, Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 8));
	//奖杯 Kelchend
	addSprite(kelchend, MAX_SCORE_FILENAME, Vec2(VISIBLE_SIZE.width / 20, VISIBLE_SIZE.height / 10));
	//奖章是否显示 Ribbon whether or not visible
	if (DataXML::getInstence()->getInitialValue("maxScore") >= 3500){
		//奖章 Ribbon
		addSprite(ribbon, RIBBON_FILENAME, Vec2(VISIBLE_SIZE.width / 1.2f, VISIBLE_SIZE.height / 1.5f));
	}
	

	//StartMenu
 	addMenu(startItem, PLAY_MAIN_1_FILENAME, PLAY_MAIN_2_FILENAME, Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2.5f), false);
 	
 	//AudioMenu
	addMenu(audioItem, AUDIOON_FILENAME, AUDIOOFF_FILENAME, Vec2(VISIBLE_SIZE.width - 50, VISIBLE_SIZE.height / 8), true);

	addAboutItem();
	return true;
}

void StartScene::onEnter() {

	Layer::onEnter();
	//MaxScoreLabel
	auto maxScoreLabel = Label::createWithSystemFont(StringUtils::format("%d",DataXML::getInstence()->getInitialValue("maxScore")), "Arial", 30);
	maxScoreLabel->setPosition(VISIBLE_SIZE.width / 15 + 5, VISIBLE_SIZE.height / 10);
	maxScoreLabel->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(maxScoreLabel);
}

//添加精灵
void StartScene::addSprite(Sprite *sp, std::string fileName, Vec2 p){
	sp = Sprite::createWithSpriteFrameName(fileName);
	sp->setPosition(p);
	this->addChild(sp);
}
//添加关于按钮
void StartScene::addAboutItem(){
	auto normal = SpriteFrameCache::getInstance()->getSpriteFrameByName(HOWTOP_1_FILENAME);
	auto select = SpriteFrameCache::getInstance()->getSpriteFrameByName(HOWTOP_2_FILENAME);
	auto aboutItem = MenuItemImage::create();
	aboutItem->setNormalSpriteFrame(normal);
	aboutItem->setSelectedSpriteFrame(select);
	aboutItem->setCallback([=](Ref * sender){
		EFFECT_MUSIC("click.mp3", audioFlag);
		auto aboutLayer = AboutLayer::create();
		this->addChild(aboutLayer);
	});
	auto aboutMenu = Menu::create(aboutItem, NULL);
	aboutMenu->setPosition(VISIBLE_SIZE.width - 150, VISIBLE_SIZE.height / 8);
	this->addChild(aboutMenu);
}

//添加按钮
void StartScene::addMenu(MenuItemImage *item, std::string normalName, std::string selName, Vec2 p, bool toggleFlag){
	auto normal = SpriteFrameCache::getInstance()->getSpriteFrameByName(normalName);
	auto selected = SpriteFrameCache::getInstance()->getSpriteFrameByName(selName);

	if (toggleFlag){
		auto audioItemON = MenuItemImage::create();
		auto audioItemOFF = MenuItemImage::create();
 		if (audioFlag)
 		{
			audioItemON->setNormalSpriteFrame(normal);
			audioItemON->setSelectedSpriteFrame(normal);
			audioItemOFF->setNormalSpriteFrame(selected);
			audioItemOFF->setSelectedSpriteFrame(selected);
			
 		}else {
			audioItemON->setNormalSpriteFrame(selected);
			audioItemON->setSelectedSpriteFrame(selected);
			audioItemOFF->setNormalSpriteFrame(normal);
			audioItemOFF->setSelectedSpriteFrame(normal);
		}
		auto toggle = MenuItemToggle::createWithCallback([=](Ref *s){
			if (audioFlag){
				EFFECT_MUSIC("click.mp3", audioFlag);
				CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
				audioFlag = false;
			}else{
				EFFECT_MUSIC("click.mp3", audioFlag);
				CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("ambience.mp3", true);			
				audioFlag = true;
			}
			DataXML::getInstence()->saveData("sound",audioFlag);
		}
		, audioItemON, audioItemOFF, NULL);
		auto Menu = Menu::create(toggle, NULL);
		Menu->setPosition(p);
		this->addChild(Menu);
	}else{
		item = MenuItemImage::create();
		item->setCallback([=](Ref * sender){
			EFFECT_MUSIC("click.mp3", audioFlag);
			auto scene = GameScene::create();
			Director::getInstance()->replaceScene(scene);
		});
		item->setNormalSpriteFrame(normal);
		item->setSelectedSpriteFrame(selected);
		item->setScale(0.7f);
		auto Menu = Menu::create(item, NULL);
		Menu->setPosition(p);
		this->addChild(Menu);
	}
}

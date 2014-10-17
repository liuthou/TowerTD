
#include "GameScene.h"
#include "GameSceneBG.h"
#include "RightMenuLayer.h"
#include "LeftMenuLayer.h"
#include "MoneyLayer.h"
#include "SimpleAudioEngine.h"

bool GameScene::init(){
	if (!Scene::init()){
		return false;
	}

	//background layer
	GameSceneBG * gameSceneBG = GameSceneBG::create();
	this->addChild(gameSceneBG);

	//right menu
	RightMenuLayer *rightmenuLayer = RightMenuLayer::create();
	this->addChild(rightmenuLayer);

	//left menu
	LeftMenuLayer * leftmenuLayer = LeftMenuLayer::create();
	this->addChild(leftmenuLayer);

	//money layer

	MoneyLayer * moneyLayer = MoneyLayer::create();
	this->addChild(moneyLayer);

	return true;
}

void GameScene::onEnter()
{
	Scene::onEnter();
	auto strFile = FileUtils::getInstance()->fullPathForFilename("battle_bgm_crusade.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(strFile.c_str(), true);
}

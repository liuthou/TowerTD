#include "LoadingScene.h"
#include "StartScene.h"
#include "PhysicsHelper.h"
#include "SimpleAudioEngine.h"
#include "GameData.h"

bool LoadingScene::init(){
	if (!Layer::init())
	{
		return false;
	}
	count = 1;
	//loading picture matter
	loadPicture();
	auto logo = Sprite::create(LOGO_FILENAME);
	logo->setVisible(true);
	logo->setPosition(480, 320);
	this->addChild(logo);

	//loading music matter
	loadMusic();
	return true;
}

void LoadingScene::loadPicture(){
	PhysicsHelper::getInstance();
	for (int i = 1; i < 6; i++)
	{
		std::string pngFileName = StringUtils::format("texture0%d.png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(pngFileName, CC_CALLBACK_1(LoadingScene::plistImageCallback, this));
	}
}

void LoadingScene::plistImageCallback(Texture2D * texture){
	std::string plistFileName = StringUtils::format("texture0%d.plist", count);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistFileName,texture);
	count++;
	if (count == 6)
	{
		auto scene = StartScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}
}

void LoadingScene::loadMusic(){
	//Ô¤¼ÓÔØ±³¾°ÒôÀÖ
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("ambience.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("chickendance.mp3");
	//Ô¤¼ÓÔØÒôÐ§
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("pickup.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("hard hit.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("arm whoosh 03.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("end.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("electric.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("click.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("die_no_blood.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("bling.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("heartbeat.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("unlocked_rooster.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("unlocked_row.mp3");
}

Scene * LoadingScene::createScene(){
	auto scene = Scene::create();
	auto layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}
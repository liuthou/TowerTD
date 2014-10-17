#include "StartScene.h"
#include "ButtonLayer.h"
#include "uiRiskLayer.h"
#include "uiHeroLayer.h"
#include "uiSkillLayer.h"
#include "uiEquipLayer.h"
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;

Scene *StartScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}

bool StartScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//Õ³Ìù°´Å¥²ã
	auto buttonLayer = ButtonLayer::create();
	this->addChild(buttonLayer, 1);
    SimpleAudioEngine::getInstance()->playBackgroundMusic("uiBackGround.mp3", true);
	return true;
}

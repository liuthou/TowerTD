#include "LoadingLayer.h"
#include "GameManager.h"
#include "cocoStudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
using namespace ui;
using namespace cocostudio;
Scene *LoadingLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingLayer::create();
	scene->addChild(layer);
	return scene;
}
bool LoadingLayer::init(){
	if(!Layer::init()){
		return false;
	}
	addSprite();
	resCount = 0;
	
	auto arminstance = ArmatureDataManager::getInstance();
	auto res = GameManager::getInstance()->resources;
	auto str = res.at("bg").asString();
	auto &prevc = GameManager::getInstance()->preEnemyTypesVector;
	auto &vc = GameManager::getInstance()->enemyTypesVector;
	resSum = vc.size();
	for (auto it = prevc.begin();it != prevc.end();it++)
	{   
		std::string fileName = (*it) + "NewAnimation";
		arminstance->removeArmatureFileInfo(fileName + ".ExportJson");
		auto file = "soldier/"+ fileName + "/" + fileName + ".ExportJson";
		log("clear:%s",file.c_str());
	}
    prevc.clear();
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
	//clear all unused res
	for (auto it = vc.begin();it != vc.end();it++)
	{ 
		std::string fileName = (*it) + "NewAnimation";
		arminstance->addArmatureFileInfoAsync(fileName + ".ExportJson",this,schedule_selector(LoadingLayer::update));
		auto file = "soldier/"+ fileName + "/" + fileName + ".ExportJson";
		log("add:%s",file.c_str());
	}
	
	 Director::getInstance()->getTextureCache()->addImageAsync(str,[&](cocos2d::Texture2D * texture){
		 update(0);
	});
	return true;
}
void LoadingLayer::addSprite()
{
	auto loading = Sprite::create("loading1.png");
	this->addChild(loading);
	loading->setScale(1.5);
	this->setPosition(Vec2(640,360));
	auto loadingBar = Sprite::create("loading_Base_chs-hd.png");
	this->addChild(loadingBar);
}
void LoadingLayer::update(float t)
{  
	resCount++;
	if (resCount > resSum)
	{
		Director::getInstance()->replaceScene(GameScene::create());
		auto str = Director::getInstance()->getTextureCache()->getCachedTextureInfo();
		log("%s",str.c_str());
	}
}
LoadingLayer::~LoadingLayer()
{
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

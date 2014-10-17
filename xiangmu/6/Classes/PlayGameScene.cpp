//
//  PlayGameScene.cpp
//  herojump
//
//  Created by lius on 14-9-19.
//
//

#include "PlayGameScene.h"
#include "HelpLayer.h"
#include "StoneLayer.h"
#include "GoldandGemLayer.h"
#include "AudioUtil.h"
#include "ToolAnimationLayer.h"
#include "EnemyLayer.h"
#include "JumpHelp.h"
#include "InjuredEffent.h"
#include "HitBodys.h"
//tool layer


bool PlayGameScene::init(){
    if (!Scene::init()) {
        return false;
    }

    pauseSceneTag = true;
	
    addChangeToolsLayer();

    
	addRoleLayer();

	addToolsLayer();

	addBackgroundLayer();

	addBroadcastLayer();

	addRoleAnimationLayer();
    reloadData();
    
    addInjuredEffect();
    return true;
}
void PlayGameScene::reloadData(){
    HitBodys::getInstance() -> clearUseToolsBaseSprite();
}

ToolAnimationLayer* PlayGameScene::getRoleAnimationLayer(){
	return this -> getChildByName<ToolAnimationLayer*>(LAYER_NAME_ROLE_ANIMATION_LAYER);
}

void PlayGameScene::addInjuredEffect(){
    auto injuredEffent = InjuredEffect::create();
    injuredEffent -> setName(LAYER_NAME_INJUREDEFFECT);
    this -> addChild(injuredEffent,10002);
}

void PlayGameScene::addRoleAnimationLayer(){
	auto roleAnimationLayer = ToolAnimationLayer::create();
	roleAnimationLayer -> setName(LAYER_NAME_ROLE_ANIMATION_LAYER);
	this -> addChild(roleAnimationLayer,10001);
}
void PlayGameScene::onEnter(){
    Scene::onEnter();
    auto audioInstance =AudioUtil::getInstance();
    if (audioInstance->getIsBackGround()) {
        audioInstance->stopBackGroundPlay();
    }
    pauseSceneMenu();
    audioInstance->playBackgroundSound("GameBackGround.wav");
}

void PlayGameScene::pauseSceneMenu(){
    auto itemPause1 = MenuItemImage::create("pause1.png", "pause1.png");
    auto itemPause2 = MenuItemImage::create("pause2.png", "pause2.png");
    auto menuToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(PlayGameScene::pauseSceneMethod, this), itemPause1,itemPause2,NULL);
    auto menu = Menu::create(menuToggle,NULL);
    menu->setPosition(30,900);
    this->addChild(menu,1000);
    
}

void PlayGameScene::pauseSceneMethod(Ref * sender){
    if (pauseSceneTag){
        Director::getInstance()->pause();
        pauseSceneTag = false;
        JumpHelp::getRoleLayer() -> accelerationFlag = false;
    }
    else{
        Director::getInstance()->resume();
        pauseSceneTag = true;
        JumpHelp::getRoleLayer() -> accelerationFlag = true;
    }
    
}
void PlayGameScene::addRoleLayer(){
    auto roleLayer = RoleLayer::create();
    roleLayer -> setName(LAYER_NAME_ROLELAYER);
    this -> addChild(roleLayer,998);
}


RoleLayer* PlayGameScene::getRoleLayer(){
    return this -> getChildByName<RoleLayer*>(LAYER_NAME_ROLELAYER);
}
ChooseToolsLayer* PlayGameScene::getChooseToolsLayer(){
    return this -> getChildByName<ChooseToolsLayer*>(LAYER_NAME_CHANGE_TOOLS);
}
void PlayGameScene::addToolsLayer(){
    auto toolsLayer = ToolsLayer::create();
    toolsLayer -> setName(LAYER_NAME_TOOLSLAYER);
    this -> addChild(toolsLayer,1000);
}

ToolsLayer* PlayGameScene::getToolsLayer(){
    return this -> getChildByName<ToolsLayer*>(LAYER_NAME_TOOLSLAYER);
}

BackgroundLayer * PlayGameScene::getBackgroundLayer(){
    return this -> getChildByName<BackgroundLayer*>(LAYER_NAME_BACKGROUNDLAYER);
}

void PlayGameScene::addChangeToolsLayer(){
    auto toolsLayer = ChooseToolsLayer::create();
    toolsLayer -> setName(LAYER_NAME_CHANGE_TOOLS);
    this -> addChild(toolsLayer,1001);
}

void PlayGameScene::addBackgroundLayer(){
	//AudioUtil::getInstance()->playBackgroundSound("GameBackGround.mp3");
    auto backgroundLayer = BackgroundLayer::create();
    backgroundLayer -> setName(LAYER_NAME_BACKGROUNDLAYER);
    this -> addChild(backgroundLayer,997);
}

void PlayGameScene::addBroadcastLayer(){
    auto broadcastLayer = BroadcastLayer::create();
    broadcastLayer -> setName(LAYER_NAME_BROADCASTLAYER);
    this -> addChild(broadcastLayer,996);
    
}
ScoreLayer* PlayGameScene::getScoreLayer(){
    return nullptr;
}

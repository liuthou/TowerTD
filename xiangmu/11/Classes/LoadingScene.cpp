//
//  LoadingScene.cpp
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-26.
//
//

#include "LoadingScene.h"
#include "Global.h"

#include "LoginScene.h"

#include <cocostudio/CocoStudio.h>
using namespace cocostudio;

#include <tinyxml2/tinyxml2.h>
using namespace tinyxml2;

bool LoadingScene::init(){
    if (!Layer::init()) {
        return false;
    }
    
    return true;
}

void LoadingScene::onEnter(){
    initUI();
}

void LoadingScene::initUI(){
    
    auto uiLayer = GUIReader::getInstance()->widgetFromJsonFile("UI/loading.ExportJson");
    uiLayer->setPosition(Vec2::ZERO);
    this->addChild(uiLayer);
    
    auto uiPanel = uiLayer->getChildByName("Panel_6");
    
    processLabel = (Text *)uiPanel->getChildByName("Label_10");
    processBar = (LoadingBar *)uiPanel->getChildByName("ProgressBar_3");

    processValue = 0;
    
//    loadPlist();
    loadPNG();
    
}

void LoadingScene::initAudio(){
    //加载音乐缓存
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("AUDIO/back.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("AUDIO/sng_bgm.mp3");

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("AUDIO/fapai1.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("AUDIO/foldpai.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("AUDIO/button.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("AUDIO/fold_boy.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("AUDIO/fold_girl.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("AUDIO/chip.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("AUDIO/call_boy.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("AUDIO/call_girl.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("AUDIO/raise_boy.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("AUDIO/raise_girl.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("AUDIO/allin_boy.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("AUDIO/allin_girl.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("AUDIO/check_boy.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("AUDIO/check_girl.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("AUDIO/fapai2.mp3");
    
}

void LoadingScene::loadPNG(){
    Director::getInstance()->getTextureCache()->addImageAsync("UI/user.png", CC_CALLBACK_1(LoadingScene::onProcess, this));

    Director::getInstance()->getTextureCache()->addImageAsync("UI/GameScene.png", CC_CALLBACK_1(LoadingScene::onProcess, this));

    Director::getInstance()->getTextureCache()->addImageAsync("UI/Main.png", CC_CALLBACK_1(LoadingScene::onProcess, this));

    Director::getInstance()->getTextureCache()->addImageAsync("UI/Start.png", CC_CALLBACK_1(LoadingScene::onProcess, this));

    Director::getInstance()->getTextureCache()->addImageAsync("ANIMATION/girl.png", CC_CALLBACK_1(LoadingScene::onProcess, this));

    Director::getInstance()->getTextureCache()->addImageAsync("MAP/map_card1.png", CC_CALLBACK_1(LoadingScene::onProcess, this));

    Director::getInstance()->getTextureCache()->addImageAsync("MAP/map_card2.png", CC_CALLBACK_1(LoadingScene::onProcess, this));

    Director::getInstance()->getTextureCache()->addImageAsync("MAP/map_card3.png", CC_CALLBACK_1(LoadingScene::onProcess, this));

    Director::getInstance()->getTextureCache()->addImageAsync("MAP/map_card4.png", CC_CALLBACK_1(LoadingScene::onProcess, this));
    Director::getInstance()->getTextureCache()->addImageAsync("ANIMATION/pokerExt.png", CC_CALLBACK_1(LoadingScene::onProcess, this));
    
}

void LoadingScene::loadPlist(){
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ANIMATION/pokerExt.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("UI/user.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ANIMATION/girl.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("UI/dezhoupuke_dezhoupuke0.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("UI/GameScene.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("UI/Main.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("UI/Start.plist");
    
    loadScene();
}

void LoadingScene::loadScene(){
    auto scene = LoginScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.3, scene));
}

void LoadingScene::onProcess(Texture2D* t2d){
    processValue += 10.0f;
    
    if(processValue>=100.0f){
        
        loadPlist();
        
    }
    
    auto lm_vm = Config::LANGUAGE::getInstance()->AT("LoadingScene").asValueMap();

    processLabel->setString(StringUtils::format("%s...(%.0f%%)",
                            lm_vm.at("processLabel").asString().c_str(),
                            processValue));
    
    processBar->setPercent(processValue);
}

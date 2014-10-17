//
//  LoginScene.cpp
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-26.
//
//

#include "LoginScene.h"
#include "Global.h"

#include "MainScene.h"

#include <cocostudio/CocoStudio.h>
using namespace cocostudio;

bool LoginScene::init(){
    if (!Layer::init()) {
        return false;
    }
    
    initUI();
    
    return true;
}

void LoginScene::onExit(){
    Layer::onExit();
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("UI/Start.plist");
    
}
void LoginScene::initUI(){
    
    auto uiLayer = GUIReader::getInstance()->widgetFromJsonFile("UI/start.ExportJson");
    uiLayer->setPosition(Vec2::ZERO);
    this->addChild(uiLayer);
    
    singleButton = (Button *)uiLayer->getChildByName("singleButton");
    weixinButton = (Button *)uiLayer->getChildByName("weixinButton");
    weiboButton = (Button *)uiLayer->getChildByName("weiboButton");
    qqButton = (Button *)uiLayer->getChildByName("qqButton");
    
    singleButton->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(
         CC_CALLBACK_2(LoginScene::onTouchButton, this)
     ));
}

void LoginScene::onTouchButton(Ref*ref,ui::Widget::TouchEventType type){
    SinglePlay();
}

void LoginScene::SinglePlay(){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AUDIO/button.mp3");
    
    auto scene = MainScene::createScene();
    Director::getInstance()->replaceScene(scene);
}


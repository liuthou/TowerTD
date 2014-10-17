//
//  MainScene.cpp
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-26.
//
//

#include "MainScene.h"


#include "Global.h"

#include <cocostudio/CocoStudio.h>
using namespace cocostudio;

#include "Hall.h"


bool MainScene::init(){
    if (!Layer::init()) {
        return false;
    }
    auto img = new Image();
    img->initWithImageFile("UI/city_icon.png");
    Director::getInstance()->getTextureCache()->addImage(img, "city_icon.png");
    delete img;
    
    initUI();
    
    return true;
}

void MainScene::onEnter(){
    Layer::onEnter();
    
    initAudio();
}

void MainScene::onExit(){
    Layer::onExit();
    
    
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("UI/Main.plist");
}

void MainScene::initUI(){
    
    auto uiLayer = GUIReader::getInstance()->widgetFromJsonFile("UI/main.ExportJson");
    uiLayer->setPosition(Vec2::ZERO);
    this->addChild(uiLayer);
    
    
    initButtonBG();
    
    initCityIcon();

}

void MainScene::initAudio(){
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("AUDIO/sng_bgm.mp3",true);
}

void MainScene::onTouchButton(Ref*ref,ui::Widget::TouchEventType type){
    auto scene = Room::createScene(1,2000000,5);
    Director::getInstance()->replaceScene(scene);
}

void MainScene::initButtonBG(){
    
    for(int i = 1 ; i<5; i++){
        std::string fileName = StringUtils::format("MAP/map_card%d.png",i);
        
        cardMenu = Menu::create();
        cardMenu->setPosition(Vec2(0, 0));
        this->addChild(cardMenu);
        
        auto language = TexasPoker::Config::LANGUAGE::getInstance()->AT("MainScene").asValueMap();
        std::string minScoreString  = language.at("MinScore").asString();
        std::string maxScoreString  = language.at("MaxScore").asString();
        std::string noLimitString  = language.at("NoLimit").asString();
        
        auto unit = TexasPoker::Config::LANGUAGE::getInstance()->AT("Unit").asValueMap();
        std::string wanString  = unit.at("wan").asString();
        
        if(i == 1){
            card1Bg = MenuItemImage::create(fileName, fileName,fileName);
            card1Bg->setPosition(Vec2(250,320));
            cardMenu->addChild(card1Bg);
            
            float x = card1Bg->getContentSize().width/2;
            float y = card1Bg->getContentSize().height;
            
            card1Label = Label::createWithSystemFont(
                                StringUtils::format("%s 800\n%s 2000",minScoreString.c_str(),maxScoreString.c_str()),
                                "Arial", 24);
            card1Label->setPosition(x, y - 80);
            card1Bg->addChild(card1Label);

            card1Sprite = Sprite::create("MAP/CITY/city_china.png");
            card1Sprite->setPosition(x, card1Sprite->getContentSize().height/2);
            card1Bg->addChild(card1Sprite);
            
            card1Bg->setCallback(CC_CALLBACK_1(MainScene::onMenu1, this));
            
//            auto hType = new Hall::HallType();
//            *hType = Hall::HallType::CHINA;
//            card1Bg->setUserData(&hType);
            
        }else if (i ==2){
            card2Bg = MenuItemImage::create(fileName, fileName,fileName);
            card2Bg->setPosition(Vec2(568,320));
            cardMenu->addChild(card2Bg);
            
            float x = card2Bg->getContentSize().width/2;
            float y = card2Bg->getContentSize().height;
            
             card2Label = Label::createWithSystemFont(
                        StringUtils::format("%s 5000\n%s 1%s",minScoreString.c_str(),maxScoreString.c_str(),wanString.c_str()),
                                                      "Arial", 24);
             card2Label->setPosition(x, y - 80);
             card2Bg->addChild(card2Label);
            
            card2Sprite = Sprite::create("MAP/CITY/city_newyork.png");
            card2Sprite->setPosition(x, card2Sprite->getContentSize().height/2);
            card2Bg->addChild(card2Sprite);
            
        }else if (i ==3 ){
            card3Bg = MenuItemImage::create(fileName, fileName,fileName);
            card3Bg->setPosition(Vec2(886,320));
            cardMenu->addChild(card3Bg);
            
            float x = card3Bg->getContentSize().width/2;
            float y = card3Bg->getContentSize().height;
            
             card3Label = Label::createWithSystemFont(
                        StringUtils::format("%s 1%s\n%s %s",minScoreString.c_str(),wanString.c_str(), maxScoreString.c_str(),noLimitString.c_str()), "Arial", 24);
             card3Label->setPosition(x, y - 80);
             card3Bg->addChild(card3Label);
            
            card3Sprite = Sprite::create("MAP/CITY/city_lasvegas.png");
            card3Sprite->setPosition(x, card3Sprite->getContentSize().height/2);
            card3Bg->addChild(card3Sprite);
            
        }
    }
}

void MainScene::onMenu1(Ref * ref){
    log("MainScene::onMenu1");
    
//    auto menuItem = static_cast<MenuItemImage*>(ref);
//    auto hType = (Hall::HallType *)menuItem->getUserData();
    
//    log("Type : %d",(int)*hType );
    
//    if ( *hType == Hall::HallType::CHINA) {
        Hall::createRoom(Hall::HallType::CHINA);
//    }
}

void MainScene::initCityIcon(){
    auto t2d = Director::getInstance()->getTextureCache()->getTextureForKey("city_icon.png");
    
    auto preSprice = Sprite::createWithTexture(t2d, Rect(177, 0, 83, 77));
    PreButton = MenuItemSprite::create(preSprice, preSprice);
    PreButton->setPosition(50, 320);
    
    auto nextSprice = Sprite::createWithTexture(t2d, Rect(269, 0, 83, 77));
    NextButton = MenuItemSprite::create(nextSprice, nextSprice);
    NextButton->setPosition(1136 - 50, 320);
    
    auto menu = Menu::create(PreButton,NextButton,  NULL);
    menu->setPosition(0, 0);
    this->addChild(menu);
}



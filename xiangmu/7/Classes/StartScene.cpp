#include "StartScene.h"
#include "GameScene.h"
#include "SetingLayer.h"
#include "RoleAnimate.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "cocos2d.h"
using namespace ui;
using namespace cocostudio;

#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

void StartScene::onEnter(){
	Scene::onEnter();
	

}

bool StartScene::init(){
	if (!Scene::init()){
		return false;
	}
	//
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Boss3.wav",true);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hero.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bullet1.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BossTwo.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("stage1.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("stage2.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fire.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tool.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("start.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("LivesRemaining.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("boss3.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BossTwo.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("stage4.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("HeroBullet.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Explode.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("heroBorn.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BossFour.plist");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("bgMusic.mp3");
	auto bg = Sprite::createWithSpriteFrameName("startBG1.png");
	bg->setPosition(480,320);
	this->addChild(bg);

	auto wing3 = Sprite::createWithSpriteFrameName("wing_01.png");
	wing3->setScale(1.1);
	wing3->setRotation(10);
	wing3->setPosition(490,350);
	this->addChild(wing3);

	std::vector<std::string>fireFileName;
	for (int i = 1; i < 9; i++){
		std::string fileName = StringUtils::format("wing_0%d.png",i);
		fireFileName.push_back(fileName);
	}
	auto wingAni = RoleAnimate::getinstance()->createAnimate(fireFileName,0.2,-1);
	wing3->runAction(wingAni);

	auto title = Sprite::createWithSpriteFrameName("title.png");
	title->setPosition(480,240);
	title->setScale(1.1);
	this->addChild(title);

	auto startItem = MenuItemImage::create("start1.png","start1.png",[=](Ref * sender){
		//µΩ”Œœ∑≥°æ∞
		auto scene = GameScene::create();
	//	auto scene1 = TransitionZoomFlipY::create(0.6,scene);
		Director::getInstance()->replaceScene(scene);
	});
	startItem->setPosition(220,130);

    //设置
	auto setItem = MenuItemImage::create("set.png","set.png",[=](Ref * sender){
       
        cocos2d::ui::Widget *setMenu = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("Set/GameOver_1.ExportJson");
      
        this->addChild(setMenu,900);
        
        auto image = (ImageView *)setMenu->getChildByName("Image_3");
        image->setScale(15);
        auto con = (Button *)image->getChildByName("continue");
        con->addTouchEventListener([=](Ref*,Widget::TouchEventType){
            setMenu->setVisible(false);
            Director::getInstance()->resume();
        });
        //返回
       /* auto _quit = (Button *)image->getChildByName("quit");
        _quit->addTouchEventListener([=](Ref*,Widget::TouchEventType){
            exit(0);
        });*/
        //音乐
        auto _yinyue = (CheckBox *)image->getChildByName("bg_music");
        _yinyue->addEventListener([=](Ref* obj,CheckBox::EventType t){
            if(t == CheckBox::EventType::SELECTED){
                SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
				auto e = AllVectors::getInstance()->getBgmusic();
				AllVectors::getInstance()->setBgmusic(!e);
            }else{
				AllVectors::getInstance()->setBgmusic(false);
                SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
            }
        });
        //音效
		//auto ef_music = AllVectors::getInstance()->getEfmusic();

        auto _yinxiao = (CheckBox *)image->getChildByName("yinxiao_music");
        _yinxiao->addEventListener([=](Ref* obj,CheckBox::EventType t){
			auto e = AllVectors::getInstance()->getEfmusic();
			AllVectors::getInstance()->setEfmusic(!e);
        });
       //关闭
       /* auto close = (CheckBox *)image->getChildByName("close");
        close->addTouchEventListener([=](Ref*,Widget::TouchEventType){
            setMenu->setVisible(false);
        });*/
        
    });
    setItem->setPosition(800,120);
    
    auto helpItem = MenuItemImage::create("help.png","help.png",[=](Ref * sender){
        
        Widget *helpLayer = GUIReader::getInstance()->widgetFromJsonFile("HelpLayer_2/HelpLayer_1.ExportJson");
        helpLayer->setName("helplayer");
        this->addChild(helpLayer);
        auto image = (ImageView *)helpLayer->getChildByName("Image_53");
        auto closeButton = (Button *)image->getChildByName("closeButton");
        
        closeButton->addTouchEventListener([=](Ref* target,Widget::TouchEventType t){
            if (t == Widget::TouchEventType::ENDED){
                helpLayer->setVisible(false);
            }
        });
        
    });
    
    
    
    helpItem->setPosition(900,600);
    
    auto menu = Menu::create(startItem,setItem,helpItem,NULL);
    menu->setPosition(0,0);
    this->addChild(menu);
    
    
    
    
    
    return true;
}
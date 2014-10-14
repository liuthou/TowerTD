#include "StartScene.h"
#include "SelectLayer.h"
#include "LoadingLayer.h"
#include "GameScene.h"
#include "GameManager.h"
#include "HelpLayer.h"
Scene *StartScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}
bool StartScene::init(){
	if(!Layer::init()){
		return false;
	} 
	auto simple = SimpleAudioEngine::getInstance();

	auto uilayer = GUIReader::getInstance()->widgetFromJsonFile("startUI/Start.json");
	this->addChild(uilayer);
	auto btnStart = dynamic_cast<Button *>(uilayer->getChildByName("btn_start"));
	btnStart->addTouchEventListener([](Ref* ref,Widget::TouchEventType t){
		if (t == Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->replaceScene(SelectLayer::createScene());
			SimpleAudioEngine::getInstance()->playEffect("Music/btnOver.mp3");
		}
		
	}); // button start game
	auto btnExit = dynamic_cast<Button *>(uilayer->getChildByName("btn_exit"));
	btnExit->addTouchEventListener([](Ref* ref,Widget::TouchEventType t){
		if (t == Widget::TouchEventType::ENDED)
		{   
			SimpleAudioEngine::getInstance()->playEffect("Music/btnOver.mp3");
			Director::getInstance()->end();
		}

	});//exit game
	auto btnHelp = dynamic_cast<Button *>(uilayer->getChildByName("help"));
	btnHelp->addTouchEventListener([=](Ref* ref,Widget::TouchEventType t){
		if (t == Widget::TouchEventType::BEGAN)
		{   
			Director::getInstance()->replaceScene(LevelLayer::createScene());
		}

	});
	auto instance = SimpleAudioEngine::getInstance();
	auto check = dynamic_cast<CheckBox*> (uilayer->getChildByName("music_check"));
	auto isMusicON = UserDefault::getInstance()->getBoolForKey("isMusicON",true);
	 instance->playBackgroundMusic("Music/battle1.mp3",true);
	if (isMusicON)
	{     
		  check->setSelectedState(false); 
	}
	else
	{   
		check->setSelectedState(true);
		instance->pauseBackgroundMusic();
		instance->setEffectsVolume(0.0f);
	}
	check->addEventListener([=](Ref* r,CheckBox::EventType t){
		if (t == CheckBox::EventType::SELECTED)
		{   
			UserDefault::getInstance()->setBoolForKey("isMusicON",false);
		   // SimpleAudioEngine::getInstance()->stopAllEffects();
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			instance->setEffectsVolume(0.0f);
		}else
		{  
			UserDefault::getInstance()->setBoolForKey("isMusicON",true);
		    SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		}
	});
	auto money = GameManager::getInstance()->getStageMoney();
	log("%d................",money);
	return true;
}
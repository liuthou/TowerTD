#include "PauseLayer.h"
#include "GameManager.h"
#include "GameScene.h"
#include "SelectLayer.h"
bool PauseLayer::init(){
	if(!Layer::init()){
		return false;
	}
	auto uilayer = GUIReader::getInstance()->widgetFromJsonFile("startUI/Pause.json");
	this->addChild(uilayer);
	auto pausebg = uilayer->getChildByName("pause_bg");
	auto btnClose = dynamic_cast<Button *>(pausebg->getChildByName("close"));
	btnClose->addTouchEventListener([&](Ref *ref,Widget::TouchEventType t){
		      if (t == Widget::TouchEventType::ENDED)
		      {
				  GameManager::getInstance()->resume();
				  auto call = CallFunc::create([&](){this->removeFromParentAndCleanup(true);});
				  auto scal = ScaleBy::create(0.2,0,0,0);
				  this->runAction(Sequence::create(scal,call,nullptr));
		      }
	});
	auto btnRestar = dynamic_cast<Button *>(pausebg->getChildByName("restar"));
	btnRestar->addTouchEventListener([&](Ref *ref,Widget::TouchEventType t){
		if (t == Widget::TouchEventType::ENDED)
		{   
			GameManager::getInstance()->cleanAllVector();
			Director::getInstance()->replaceScene(GameScene::create());
		}

	});
	auto btnQuit = dynamic_cast<Button *>(pausebg->getChildByName("quit"));
	btnQuit->addTouchEventListener([&](Ref *ref,Widget::TouchEventType t){
		if (t == Widget::TouchEventType::ENDED)
		{
			GameManager::getInstance()->cleanAllVector();
			Director::getInstance()->replaceScene(SelectLayer::createScene());
		}
	});
	auto audioState = dynamic_cast<CheckBox *>(pausebg->getChildByName("music_select"));
	auto music = UserDefault::getInstance()->getBoolForKey("isMusicON",true);
	if (music)
	{
		audioState->setSelectedState(false);
	}
	else
	{
		audioState->setSelectedState(true);
	}
	audioState->addEventListener([=](Ref* r,CheckBox::EventType t){
		if (t == CheckBox::EventType::SELECTED)
		{   
			UserDefault::getInstance()->setBoolForKey("isMusicON",false);
			SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		}else
		{   
			UserDefault::getInstance()->setBoolForKey("isMusicON",true);
			SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		}
	});
	return true;
}
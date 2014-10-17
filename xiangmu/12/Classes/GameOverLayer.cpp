#include "GameOverLayer.h"
#include "GameBasic.h"
#include "GameManager.h"
#include "StartScene.h"
#include "SelectLayer.h"
#include "LoadingLayer.h"
#include "GameScene.h"
GameOverLayer *GameOverLayer::create(int type)
{
	auto pef = new GameOverLayer();
	if (pef&&pef->init(type))
	{
		pef->autorelease();
        return pef;
	}
	CC_SAFE_DELETE(pef);
	return nullptr;
}
bool GameOverLayer::init(int type){
	if(!Layer::init()){
		return false;
	}
	
	Widget * uilayer = nullptr;
	if (type == 0)
	{
	    uilayer = GUIReader::getInstance()->widgetFromJsonFile("GameWin.json");
		this->addChild(uilayer);
		auto btnNext = dynamic_cast<Button *>(uilayer->getChildByName("next"));
		btnNext->addTouchEventListener([&](Ref *ref,Widget::TouchEventType t){
		if (t == Widget::TouchEventType::ENDED)
			{
				
				auto call = CallFunc::create([&](){
				GameManager::getInstance()->nextStage();
				if (GameManager::getInstance()->curlevel <= TOWERNUMBER)
				{   
					std::string str = StringUtils::format("tower_%d",GameManager::getInstance()->curlevel);
					UserDefault::getInstance()->setBoolForKey(str.c_str(),true);
				}
				Director::getInstance()->replaceScene(LoadingLayer::createScene());
				});
				auto scal = ScaleBy::create(0.2,0,0,0);
				this->runAction(Sequence::create(scal,call,nullptr));
			}
		});
        auto num = UserDefault::getInstance()->getIntegerForKey("curNum");
        auto max = num > GameManager::getInstance()->curlevel ? num:GameManager::getInstance()->curlevel;
        UserDefault::getInstance()->setIntegerForKey("curNum",max);
	}
	if (type == 1)
	{
		uilayer = GUIReader::getInstance()->widgetFromJsonFile("GameDefat.json");
		this->addChild(uilayer);
	}
	if (type == 2)
	{
		uilayer = GUIReader::getInstance()->widgetFromJsonFile("GameOver.json");
		this->addChild(uilayer);
	}
	auto btnRestar = dynamic_cast<Button *>(uilayer->getChildByName("restar"));
	btnRestar->addTouchEventListener([&](Ref *ref,Widget::TouchEventType t){
		if (t == Widget::TouchEventType::ENDED)
		{   
			GameManager::getInstance()->cleanAllVector();
			Director::getInstance()->replaceScene(GameScene::create());
		}
	});
	auto btnQuit = dynamic_cast<Button *>(uilayer->getChildByName("quit"));
	btnQuit->addTouchEventListener([&](Ref *ref,Widget::TouchEventType t){
		if (t == Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->replaceScene(SelectLayer::createScene());
		}
	});
	return true;
}
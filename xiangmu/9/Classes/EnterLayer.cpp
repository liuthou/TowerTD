#include "EnterLayer.h"
#include "ExorbitanceScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace cocostudio;
using namespace cocos2d::ui;
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;


Scene *EnterLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = EnterLayer::create();
	scene->addChild(layer);
	return scene;
}

bool EnterLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Widget *uiLayer1 = GUIReader::getInstance()->widgetFromJsonFile("StartUi_1.json");
	Widget *uiLayer2 = GUIReader::getInstance()->widgetFromJsonFile("StartUi_2.json");
	Widget *uiLayer3 = GUIReader::getInstance()->widgetFromJsonFile("StartUi_3.json");
	this->addChild(uiLayer1);
	uiLayer2->retain();
	uiLayer3->retain();
	uiLayer1->addTouchEventListener([=](Ref *f, Widget::TouchEventType t){
		if (t == Widget::TouchEventType::ENDED)
		{
			this->addChild(uiLayer2);
			uiLayer1->setVisible(false);
		}
	});
	uiLayer2->addTouchEventListener([=](Ref *f, Widget::TouchEventType t){
		if (t == Widget::TouchEventType::ENDED)
		{
			this->addChild(uiLayer3);
			uiLayer2->setVisible(false);
		}
	});
    
	uiLayer3->addTouchEventListener([=](Ref *f, Widget::TouchEventType t){
		if (t == Widget::TouchEventType::ENDED)
		{
			auto scene = ExorbitanceScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	});
    SimpleAudioEngine::getInstance()->playBackgroundMusic("Start1.wav", true);
	return true;
}

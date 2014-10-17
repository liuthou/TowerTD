#include "BackLayer.h"
#include "StartScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace cocostudio;
using namespace cocos2d::ui;

bool BackLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
    
	Widget *uiLayer = GUIReader::getInstance()->widgetFromJsonFile("StopUi_1.json");
	this->addChild(uiLayer);
	auto image = (ImageView *)uiLayer->getChildByName("Image_bg");
	auto button1 = (Button *)image->getChildByName("Button_1");
	auto button2 = (Button *)image->getChildByName("Button_2");
	button2->addTouchEventListener([=](Ref *f, Widget::TouchEventType t){
		if (t == Widget::TouchEventType::ENDED)
		{
            Director::getInstance()->resume();
			auto scene = StartScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	});
    
	button1->addTouchEventListener([=](Ref *f, Widget::TouchEventType t){
		if (t == Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->resume();
			this->setVisible(false);
		}
	});
    
	return true;
}
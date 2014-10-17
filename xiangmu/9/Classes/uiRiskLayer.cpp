#include "uiRiskLayer.h"
#include <tinyxml2/tinyxml2.h>
#include "loading.h"
using namespace tinyxml2;
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;

Scene *uiRiskLayer::createScene()
{
	auto sence = Scene::create();
	auto layer = uiRiskLayer::create();
	sence->addChild(layer);
	return sence;
}
bool uiRiskLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Widget * uilayer = GUIReader::getInstance()->widgetFromJsonFile("RPGUI_RISK.json");
	this->addChild(uilayer);
	//关卡的按钮实现
	for (int i = 1; i <= XMLNUMBER; i++)
	{
		auto filename = StringUtils::format(BUTTON, i);
		auto button = (Button *)uilayer->getChildByName(filename);
		button->addTouchEventListener([=](Ref * sender, Widget::TouchEventType t)
		{
			if (t == Widget::TouchEventType::ENDED)
			{
                SimpleAudioEngine::getInstance()->playEffect("select.wav");
				button->setTag(i);
				replaceScene(button);
			}
		});
	}
	return true;
}

void uiRiskLayer::replaceScene(Ref * sender)
{
	auto itemT = dynamic_cast<Button *> (sender);
	auto stringname = StringUtils::format(XML, itemT->getTag());
	Director::getInstance()->replaceScene(Loading::createScene(stringname));
}
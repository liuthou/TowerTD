#include "TemLayer.h"
#include "SystemMarcoUtil.h"
#include "storeSelectLayer.h"
#include "ui/CocosGUI.h"
using namespace ui;
bool TemLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Button * temOneSpriteButton = Button::create("tem1.png","tem1.png","tem1.png");
	temOneSpriteButton->setPosition(Vec2(GET_WINDOWS_SIZE/2));
	temOneSpriteButton->addTouchEventListener([=](Ref * sender,Widget::TouchEventType event){
		if (event == Widget::TouchEventType::ENDED)
		{
			int money = 1000;
			addStoreSelectLayer(money);
			log("=========");
		}
	});
	pageView = PageView::create();
	pageView->setContentSize(Size(640,960));

	auto laout = Layout::create();
	laout->addChild(temOneSpriteButton);
	pageView->insertPage(laout, 0);

	Button * temSecondButton = Button::create("tem2.png","tem2.png","tem2.png");
	temSecondButton->setPosition(Vec2(GET_WINDOWS_SIZE/2));
	temSecondButton->addTouchEventListener([=](Ref * sender,Widget::TouchEventType event){
		if (event == Widget::TouchEventType::ENDED)
		{
			log("*******************");
			int money = 2000;
			addStoreSelectLayer(money);	
		}
	});

	laout = Layout::create();
	laout->addChild(temSecondButton);
	pageView->insertPage(laout, 1);

	Button * temThirdButton = Button::create("tem3.png","tem3.png","tem3.png");
	temThirdButton->setPosition(Vec2(GET_WINDOWS_SIZE/2));
	temThirdButton->addTouchEventListener([=](Ref * sender,Widget::TouchEventType event){
		if (event == Widget::TouchEventType::ENDED)
		{
			int money = 3200;
			addStoreSelectLayer(money);
			log("=========");
		}
	});
    laout = Layout::create();
	laout->addChild(temThirdButton);
	pageView->insertPage(laout, 2);

	Button * temFourButton = Button::create("tem4.png","tem4.png","tem4.png");
	temFourButton->setPosition(Vec2(GET_WINDOWS_SIZE/2));
	temFourButton->addTouchEventListener([=](Ref * sender,Widget::TouchEventType event){
		if (event == Widget::TouchEventType::ENDED)
		{
			int money = 5000;
			addStoreSelectLayer(money);
			log("=========");
		}
	});
	laout = Layout::create();
	laout->addChild(temFourButton);
	pageView->insertPage(laout, 3);
	this->addChild(pageView);
	return true;

}

void TemLayer::addStoreSelectLayer(int money)
{
	StoreSelectLayer * storeSelectLayer = StoreSelectLayer::create(money);
	this->addChild(storeSelectLayer);
}


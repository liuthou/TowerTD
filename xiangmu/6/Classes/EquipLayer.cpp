#include "EquipLayer.h"
#include "SystemMarcoUtil.h"
#include "storeSelectLayer.h"
#include "ui/CocosGUI.h"
using namespace ui;
bool EquipLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Button * equipSpriteButton = Button::create("1life_05.png","1life_05.png","1life_05.png");
	equipSpriteButton->setPosition(Vec2(GET_WINDOWS_SIZE/2));
	equipSpriteButton->addTouchEventListener([=](Ref * sender,Widget::TouchEventType event){
		if (event == Widget::TouchEventType::ENDED)
		{
			int money = 00;
			addStoreSelectLayer(money);
			log("=========");
		}
	});
	pageView = PageView::create();
	pageView->setContentSize(Size(640,960));


	auto laout = Layout::create();
	laout->addChild(equipSpriteButton);
	pageView->insertPage(laout, 0);
    
	Button * equipSpriteButtonSecond = Button::create("1life_04.png","1life_04.png","1life_04.png");
	equipSpriteButtonSecond->setPosition(Vec2(GET_WINDOWS_SIZE/2));
	equipSpriteButtonSecond->addTouchEventListener([=](Ref * sender,Widget::TouchEventType event){
		if (event == Widget::TouchEventType::ENDED)
		{
			log("*******************");
			int money = 50;
			addStoreSelectLayer(money);	
		}
	});

	laout = Layout::create();
	laout->addChild(equipSpriteButtonSecond);
	pageView->insertPage(laout, 1);
    
	this->addChild(pageView);
	return true;
}

void EquipLayer::addStoreSelectLayer(int money)
{
	StoreSelectLayer * storeSelectLayer = StoreSelectLayer::create(money);
	this->addChild(storeSelectLayer);
}

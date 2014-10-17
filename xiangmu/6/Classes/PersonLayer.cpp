#include "PersonLayer.h"
#include "SystemMarcoUtil.h"
#include "ui/CocosGUI.h"
using namespace ui;
bool PersonLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Sprite * personSprite = Sprite::create("1life_01.png");
	personSprite->setPosition(Vec2(GET_WINDOWS_SIZE/2));
	//this->addChild(personSprite);
	pageView = PageView::create();
	pageView->setContentSize(Size(640,960));
	auto laout = Layout::create();
	laout->addChild(personSprite);
	pageView->insertPage(laout, 0);
	Sprite * personSprite1 = Sprite::create("1life_02.png");
	personSprite1->setPosition(Vec2(GET_WINDOWS_SIZE/2));
	laout = Layout::create();
	laout->addChild(personSprite1);
	pageView->insertPage(laout, 1);
	this->addChild(pageView);


	return true;
}


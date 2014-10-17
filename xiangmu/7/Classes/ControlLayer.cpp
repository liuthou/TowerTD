#include "ControlLayer.h"

bool ControlLayer::init(){
	if(!Layer::init()){
		return false;
	}

	isPost = true;

	vec = Vec2(0,0);

	auto dis = Director::getInstance()->getEventDispatcher();
	auto listen = EventListenerTouchOneByOne::create();
	listen->onTouchBegan = [=](Touch * t,Event * e){

		vec = t->getLocation();

		if(t->getLocation().x < Director::getInstance()->getVisibleSize().width/2){
			return true;
		}
		return false;
	};

	listen->onTouchMoved = [=](Touch * t,Event * e){
		if(this->getIsPost() == false){
			return;
		}
		if((t->getLocation().x - t->getPreviousLocation().x) > 7){
			__NotificationCenter::getInstance()->postNotification("rightMove");
		}
		if(t->getPreviousLocation().x - t->getLocation().x > 7){
			__NotificationCenter::getInstance()->postNotification("leftMove");
		}
		if(t->getLocation().y - t->getPreviousLocation().y > 12){
			__NotificationCenter::getInstance()->postNotification("Jump");
		}
	};
	listen->onTouchEnded = [=](Touch * t,Event * e){
		if(this->getIsPost() == false){
			return;
		}
		__NotificationCenter::getInstance()->postNotification("stopMove");
		__NotificationCenter::getInstance()->postNotification("Stand");
	};
	dis->addEventListenerWithSceneGraphPriority(listen,this);

	//fire°´Å¥
	MenuItemImage * fireButton = MenuItemImage::create("control_bg.png","control_bg.png",[=](Ref * sender){
		if(this->getIsPost() == false){
			return;
		}
		__NotificationCenter::getInstance()->postNotification("Fire");
	});
	Menu * menu1 = Menu::create(fireButton,nullptr);
	fireButton->setScale(0.7);
	fireButton->setOpacity(80);
	menu1->setPosition(850,100);
	this->addChild(menu1);

	//×¢²á²¶×½¼àÌý
	listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyPressed = CC_CALLBACK_2(ControlLayer::onKeyMove, this);
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(ControlLayer::onKeyStop, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);

	return true;

}

//²¶×½¼àÌý
void ControlLayer::onKeyMove(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	if(this->getIsPost() == false){
		return;
	}

	if (keycode == EventKeyboard::KeyCode::KEY_A)  //
	{
		__NotificationCenter::getInstance()->postNotification("leftMove");
	}
	if (keycode == EventKeyboard::KeyCode::KEY_D)  //
	{
		__NotificationCenter::getInstance()->postNotification("rightMove");
	}
	if (keycode == EventKeyboard::KeyCode::KEY_K)  //
	{
		__NotificationCenter::getInstance()->postNotification("Jump");
	}
	if (keycode == EventKeyboard::KeyCode::KEY_J)  //
	{
		__NotificationCenter::getInstance()->postNotification("Fire");
	}
}

void ControlLayer::onKeyStop(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	__NotificationCenter::getInstance()->postNotification("stopMove");
}

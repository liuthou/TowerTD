#include "ControlLayer.h"
#include "BaseLayer.h"

bool  ControlLayer::init() {
	if (!Layer::init()){
		return false;
	}
	initUIandRigsterHandlers();	
	return true;
}

void ControlLayer::sendMovementOrder(MovementDirection direction) {
	EventCustom eventCustom(PLAYER_MOVE);
	eventCustom.setUserData(new MovementDirection(direction));
	this->getEventDispatcher()->dispatchEvent(&eventCustom);
}

void ControlLayer::reset() {
	stop();
}

void ControlLayer::start() {
	this->setVisible(true);
	m_leftBtn->setTouchEnabled(true);
	m_rightBtn->setTouchEnabled(true);
	m_upBtn->setTouchEnabled(true);
	m_downBtn->setTouchEnabled(true);
}

void ControlLayer::stop() {
	this->setVisible(false);
	m_leftBtn->setTouchEnabled(false);
	m_rightBtn->setTouchEnabled(false);
	m_upBtn->setTouchEnabled(false);
	m_downBtn->setTouchEnabled(false);
}

void ControlLayer::initUIandRigsterHandlers() {
	Widget *uiLayer = GUIReader::getInstance()->widgetFromJsonFile("ControlLayer/ControlLayer.json");
	this->addChild(uiLayer);
	m_leftBtn = (Button *)uiLayer->getChildByName("Button_4");
	m_leftBtn->setOpacity(100);
	m_rightBtn = (Button *)uiLayer->getChildByName("Button_6");
	m_rightBtn->setOpacity(100);
	m_upBtn = (Button *)uiLayer->getChildByName("Button_5");
	m_upBtn->setOpacity(100);
	m_downBtn = (Button *)uiLayer->getChildByName("Button_7");
	m_downBtn->setOpacity(100);

	m_leftBtn->addTouchEventListener([=](Ref *sender, Widget::TouchEventType t){
		if (t == Widget::TouchEventType::ENDED)
			sendMovementOrder(LEFT);
	});

	m_rightBtn->addTouchEventListener([=](Ref *sender, Widget::TouchEventType t){
		if (t == Widget::TouchEventType::ENDED)
			sendMovementOrder(RIGHT);
	});

	m_upBtn->addTouchEventListener([=](Ref *sender, Widget::TouchEventType t){
		if (t == Widget::TouchEventType::ENDED)
			sendMovementOrder(UP);
	});

	m_downBtn->addTouchEventListener([=](Ref *sender, Widget::TouchEventType t){
		if (t == Widget::TouchEventType::ENDED)
			sendMovementOrder(DOWN);
	});
	
	stop();
}
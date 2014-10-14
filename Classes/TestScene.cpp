#include "TestScene.h"

#include "FishLayer.h"
#include "Angle.h"

bool TestScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	
	auto selectLayer = FishLayer::create();

	this->addChild(selectLayer);
	selectLayer->setAnchorPoint(Vec2::ZERO);
	auto listener = EventListenerTouchOneByOne::create();
	
	listener->onTouchBegan = [=](Touch* pTouch,Event* pEvent){
	 
		auto point = pTouch->getLocation();
		auto anchorPos = Vec2(point.x / this->getBoundingBox().size.width, point.y / this->getBoundingBox().size.height);
		
	/*	selectLayer->setPosition(Vec2(selectLayer->getContentSize().width*(anchorPos).x, selectLayer->getContentSize().height*(anchorPos).y));*/
		this->setAnchorPoint(anchorPos);
		return true;
	};
	listener->onTouchMoved = [=](Touch* pTouch,Event* pEvent){
		auto point = this->convertTouchToNodeSpace(pTouch);
	
		this->setScale(this->getScale()*pTouch->getLocation().getDistance(this->getAnchorPoint()) / pTouch->getStartLocation().getDistance(this->getAnchorPoint()));
		 
		 
	};
	listener->onTouchEnded = [=](Touch* pTouch, Event* pEvent){
		
	};
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

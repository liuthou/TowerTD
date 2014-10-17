#include "ControlLayer.h"
#include "Role.h"
#include "GameData.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "RoleLayer.h"

bool ControlLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	//初始主角正常跑，状态为true
	isNormal = true;

	addTouch();
	addGravity();

	return true;
}

void ControlLayer::onEnter(){
	Layer::onEnter();
	auto layer = GET_ROLE_LAYER;
	role = layer->getRole();
}

void ControlLayer::addGravity(){
	//开启重力感应
	Device::setAccelerometerEnabled(true);
	//创建监听对象
	auto gravityListener = EventListenerAcceleration::create([=](Acceleration * acc, Event * pevent){
		//使精灵随重力感应移动
		Vec2 position = role->getPosition();
		//判断是快跑还是慢跑
		if (acc->x > 0.2 && isNormal == true)
		{
			role->fastRun();
			isNormal = false;
		}
		else if (acc->x < -0.2 && isNormal == true)
		{
			role->slowRun();
			isNormal = false;
		}
		else if (acc->x >= -0.2 && acc->x < 0 && isNormal == false)
		{
			role->stopSlowRun();
			isNormal = true;
		}
		else if (acc->x >= 0 && acc->x <= 0.2 && isNormal == false)
		{
			role->stopFastRun();
			isNormal = true;
		}
		if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		{
			position.x += acc->x * 2;
		}else if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		{
			position.x += acc->x * 5;
		}
		role->setPosition(position);
	});
	//在事件监听器中注册
	_eventDispatcher->addEventListenerWithSceneGraphPriority(gravityListener, this);
}

void ControlLayer::addTouch(){

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [=](Touch * pTouch, Event * pEvent){
		if (role->getM_hp() <= 0)
		{
			return false;
		}
		role->jumpUp();
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}
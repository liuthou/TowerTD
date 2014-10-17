#include "ShapeBullet.h"
#include "ShapeFunc.h"
#include "GameScene.h"
ShapeBullet *ShapeBullet::create(float speed, Vec2 fromPosition, float attack, std::string fileName, Vec2 toPosition, int number){
	ShapeBullet *pRet = new ShapeBullet();
	if (pRet && pRet->init(speed, fromPosition, attack, fileName, toPosition, number))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool ShapeBullet::init(float speed, Vec2 fromPosition, float attack, std::string fileName, Vec2 toPosition, int number){
	if (!Sprite::init()){
		return false;
	}

	this->number = number;
	this->toPosition = toPosition;
	this->setSpeed(speed);

	shapeFunc *func = shapeFunc::create(speed, fromPosition, attack, fileName,toPosition,number);
	auto scene = (GameScene *)Director::getInstance()->getRunningScene();
	auto herolayer =scene->getHeroLayer();
	herolayer->addChild(func);

	return true;
}



#include "LinearBullet.h"
LinearBullet *LinearBullet::create(float speed, Vec2 fromPosition, float attack, std::string fileName,int bulletSpecies,int pro){
	LinearBullet *pRet = new LinearBullet();
	if (pRet && pRet->init(speed, fromPosition, attack, fileName,bulletSpecies,pro))
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

bool LinearBullet::init(float speed, Vec2 fromPosition, float attack, std::string fileName, int bulletSpecies, int pro){
	
	if (!BaseBullet::init(speed, fromPosition, attack, fileName,bulletSpecies,pro)){
		return false;
	}
	float dis = ccpDistance(fromPosition, Vec2(960, this->getPositionY()));
	this->setSpeed(dis/800);
	return true;
}

//执行动画，串行的运行死亡和移动动画。
void LinearBullet::onEnter(){
	Sprite::onEnter();
	if (propert != 0)
	{
		return;
	}
	Size viewSize = Director::getInstance()->getWinSize();
	auto to = MoveTo::create(this->getSpeed(), Vec2(960, this->getPositionY()));
	auto cf = CallFunc::create(std::bind(&BaseBullet::die, this));
	this->runAction(Sequence::create(to, cf, NULL));
}

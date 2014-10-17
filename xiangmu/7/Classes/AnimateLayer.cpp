#include "AnimateLayer.h"
#include "RoleAnimate.h"
bool AnimateLayer::init(){
	if(!Layer::init()){
		return false;
	}
	//0.9秒后移除精灵
	//this->scheduleOnce(schedule_selector(AnimateLayer::removeSp),0.9);
	//添加出生动画
	//addBornAnimate();
	return true;
}

void AnimateLayer::addBornAnimate(){
	//添加运行动画的精灵
	bornAnimate4 = Sprite::create();
	bornAnimate4->setPosition(700,196);
	bornAnimate4->setScaleX(0.2);
	bornAnimate4->setScaleY(0.3);
	this->addChild(bornAnimate4);
	//运行动画
	auto ani = RoleAnimate::getinstance()->getBornAnimate(4,11,0.08,1);
	bornAnimate4->runAction(ani);
}

void AnimateLayer::removeSp(float t){
	//移除运行动画的精灵
	bornAnimate4->removeFromParentAndCleanup(true);
}
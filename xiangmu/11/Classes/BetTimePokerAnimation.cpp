#include "BetTimePokerAnimation.h"
#include "Room.h"

#include "Global.h"

BetTimePokerAnimation* BetTimePokerAnimation::create(ProcessControl *processControl){
	BetTimePokerAnimation *pRet = new BetTimePokerAnimation();
	if (pRet && pRet->init(processControl)){
		pRet->autorelease();

		return pRet;
	}else{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool BetTimePokerAnimation::init(ProcessControl *processControl){
	if(!PokerAnimation::init(processControl)){
		return false;
	}

	//this->startPoint = Vec2(568, 300);
    
	initUI();

	return true;
}

void BetTimePokerAnimation::bettingTime(int index){
    log("BetTimePokerAnimation::bettingTime(int index) %d",index);
    
	playerItem = processControl->getRoom()->getPlayerItemByChairNumber(index);
	player = processControl->getRoom()->getPlayerByChairNumber(index);

    timer->setPosition(playerItem->getPosition());
    
	// 进度条进度范围 的初始化
	doingProgress = ProgressFromTo::create(BetTimePokerAnimation_BETTIME, 100.0f, 0.0f);
    
	// 色调变化
	auto tintto1 = TintTo::create(BetTimePokerAnimation_BETTIME, 255, 0,   0);
    
    //error
	//  结束回调
	auto callFunc = CallFunc::create(CC_CALLBACK_0(BetTimePokerAnimation::bettingTimeEnd, this));

	auto spa = Spawn::create(doingProgress, tintto1, NULL);
    
	timer->runAction(
        Sequence::create(spa,callFunc, NULL)
    );
}

void BetTimePokerAnimation::bettingTimeEnd(){
    timer->stopAllActions();
    this->removeChild(timer);
    
    End();
}

void BetTimePokerAnimation::initUI(){    
	// 动画
	spShape = Sprite::create("UI/BettingTime02.png");
    
    // 进度条计时器 的初始化 和 属性设置
    timer = ProgressTimer::create(spShape);
    timer->setType(ProgressTimer::Type::RADIAL);
    this->addChild(timer);
    
    timer->setPercentage(100);
    timer->setReverseDirection(true);
}


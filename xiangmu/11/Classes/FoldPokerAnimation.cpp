#include "FoldPokerAnimation.h"
#include "Room.h"

FoldPokerAnimation* FoldPokerAnimation::create(ProcessControl *processControl){
	FoldPokerAnimation *pRet = new FoldPokerAnimation();
	if (pRet && pRet->init(processControl)){
		pRet->autorelease();

		return pRet;
	}
	else{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool FoldPokerAnimation::init(ProcessControl *processControl){
	if (!PokerAnimation::init(processControl)){
		return false;
	}

	this->endPoint = Vec2(568, 300);

    initUI();
    
	return true;
}

void FoldPokerAnimation::initUI(){
    foldSprite = Sprite::create("UI/fold.png");
    this->addChild(foldSprite);
}

void FoldPokerAnimation::fold(int index){
    log("FoldPokerAnimation::fold %d",index);

    /**
	*发牌有椅子处开始
	*点击发牌后，让自己的牌隐藏掉（可以亮度降低\或者直接消失于屏幕上）
	*触发动画，河牌移动到桌子中间（带旋转效果），并最终消失在屏幕上
	*/

	//根据椅子号取到玩家
	playerItem = processControl->getRoom()->getPlayerItemByChairNumber(index);

    //取出玩家位置,弃牌动作由玩家位置处开始
	startPoint = playerItem->getPosition();

	foldSprite->setPosition(startPoint);    

	//根据椅子，取出玩家
	player = processControl->getRoom()->getPlayerByChairNumber(index);

    //求出从椅子到牌桌中心点的距离
	float distance = endPoint.distance(playerItem->getPosition());

	//移动时间
	float t = distance / 1000;
    
	dealMoveTo = MoveTo::create(t, endPoint);

	float jiaodu = TexasPoker::Function::getAngleByVec21ANDVec22(startPoint, playerItem->getPosition());
	foldSprite->setRotation(jiaodu);

	auto callFunc = CallFunc::create(CC_CALLBACK_0(FoldPokerAnimation::End, this));
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AUDIO/foldpai.mp3");
    
    foldSprite->runAction(
        Sequence::create(dealMoveTo, callFunc, NULL)
    );
}

void FoldPokerAnimation::End(){
    log("FoldPokerAnimation::End");
    
    //弃牌,变色
    playerItem->setColor(Color3B::GRAY);
    
	endFunc();
}


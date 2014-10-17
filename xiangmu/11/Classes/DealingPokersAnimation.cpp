//
//  DealingPokersAnimation.cpp
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-29.
//
//

#include "DealingPokersAnimation.h"
#include "Room.h"
#include "Global.h"

void DealingPokersAnimation::dealing(int index){
    
    dealSprite->setVisible(true);
    
    playerItem = processControl->getRoom()->getPlayerItemByChairNumber(index);
    player = processControl->getRoom()->getPlayerByChairNumber(index);
    
    float distance = startPoint.distance(playerItem->getPosition());
    
    dealMoveTo = MoveTo::create( distance / DealingPokersAnimation_dealMoveTime, playerItem->getPosition());
    
    float jiaodu = TexasPoker::Function::getAngleByVec21ANDVec22(startPoint,playerItem->getPosition());
    dealSprite->setRotation(jiaodu);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AUDIO/fapai1.mp3");

    
    auto callFunc = CallFunc::create(CC_CALLBACK_0(DealingPokersAnimation::dealingEnd, this));
    
    dealSprite->runAction(
          Spawn::create(fapaiAnimate,
          Sequence::create(dealMoveTo,callFunc, NULL),
                        NULL)
    );
}

void DealingPokersAnimation::dealingEnd(){    
    
    if (playerItem->getChildByTag(1001) == nullptr) {
        auto it1 = player->getPoker_Array()->getHandVector();
        auto it = it1.begin();
        (*it)->setPosition(Vec2(40,80));
        playerItem->addChild(*it,1,1001);
    }else if (playerItem->getChildByTag(1002) == nullptr){
        auto it2 = player->getPoker_Array()->getHandVector();
        auto it = it2.begin();
        it++;
        (*it)->setPosition(Vec2(70,80));
        playerItem->addChild(*it,1,1002);
    }
    
    End();
}

bool DealingPokersAnimation::init(ProcessControl *processControl){
    if(!PokerAnimation::init(processControl)){
        return false;
    }
    
    this->startPoint = Vec2(568, 300);

    initUI();
    
    return true;
}

void DealingPokersAnimation::initUI(){    
    dealSprite = Sprite::createWithSpriteFrameName("poker_fapai_1.png");
    dealSprite->setPosition(startPoint);
    dealSprite->setScale(0.5);
    this->addChild(dealSprite);
    
    Animation* fapai = AnimationCache::getInstance()->getAnimation("fapai");
    if (fapai == nullptr) {
        fapai = Animation::create();
        for (int i=1; i<6; i++) {
            fapai->addSpriteFrame(
                  SpriteFrameCache::getInstance()->getSpriteFrameByName(
                        StringUtils::format("poker_fapai_%d.png",i))
            );
        }
        fapai->setDelayPerUnit(0.05f);
        fapai->setLoops(1);
        AnimationCache::getInstance()->addAnimation(fapai, "fapai");
    }
    
    fapaiAnimate = Animate::create(fapai);
}

DealingPokersAnimation* DealingPokersAnimation::create(ProcessControl *processControl){
    DealingPokersAnimation *pRet = new DealingPokersAnimation();
    if (pRet && pRet->init(processControl)){
        pRet->autorelease();
        
        return pRet;
    }else{
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
//
//  PokerAnimation.cpp
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-29.
//
//

#include "PokerAnimation.h"

void PokerAnimation::End(){
    
    auto _endFunc = endFunc;
    
    try{
        this->removeFromParentAndCleanup(true);
    }catch(...){
        ;
    }
    
    _endFunc();
}

void PokerAnimation::setEndFunc(std::function<void ()> endFunc){
    this->endFunc = endFunc;
}

bool PokerAnimation::init(ProcessControl *processControl){
    if(!Layer::init()){
        return false;
    }
    
    this->processControl = processControl;
    return true;
}

PokerAnimation* PokerAnimation::create(ProcessControl *processControl){
    PokerAnimation *pRet = new PokerAnimation();
    if (pRet && pRet->init(processControl)){
        pRet->autorelease();
        
        return pRet;
    }else{
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


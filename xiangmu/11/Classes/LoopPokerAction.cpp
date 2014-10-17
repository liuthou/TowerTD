//
//  LoopPokerAction.cpp
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-13.
//
//

#include "LoopPokerAction.h"
#include "PokerAction.h"
#include "ProcessControl.h"
#include "AiPlayerAction.h"

#include "Global.h"

using namespace TexasPoker;

LoopPokerAction * LoopPokerAction::create(ProcessControl * processControl){
	LoopPokerAction *pRet = new LoopPokerAction();
	
	if (pRet) {

        pRet->autorelease();
        
        pRet->processControl = processControl;
        
        // 获得当前玩家
        pRet->betingPlayer = processControl->getBetingPlayer();

		// 设置 流程结束的玩家( 第一轮是 大盲注，第二轮 是 小盲注)
		pRet->lastPlayer = processControl->PrePlayer(pRet->betingPlayer->getPlayerIndex());
        
        pRet->lastRaisePlayer = nullptr;
        
        return pRet;
	} else{
        delete pRet;
        pRet = NULL; 
        return NULL; 
	}
}

void LoopPokerAction::BetEnd(){
    TP::log("LoopPokerAction::BetEnd; lastPlayer:%p",lastPlayer);
    
	if (betingPlayer == lastPlayer){
        log("LoopPokerAction::BetEnd endFunc()");
        auto _endFunc = endFunc;
        try{
            this->removeFromParentAndCleanup(true);
        }catch(...){
            ;
        }
        
		_endFunc();
        
	}else{
        
        auto tempBetingPlayer = beginPlayer;
        betingPlayer = processControl->NextPlayer(betingPlayer->getPlayerIndex());
        processControl->setBetingPlayer(betingPlayer);
        
        log("LoopPokerAction::BetEnd betingPlayer: %p playIndex: %d",betingPlayer,betingPlayer->getPlayerIndex());
        
        if(tempBetingPlayer == betingPlayer){
            log("tempBetingPlayer == betingPlayer");
            this->endFunc();
        }
        
		// PokerAction 中的一些东西 要写成 virtual 才可以在这里使用
        
		//创建玩家操作 Layer，也即 PokerAction
        PokerAction * pokerAction = nullptr ;
		if (betingPlayer->getPlayerType() == ePlayerType::NORMAL)
		{
			pokerAction = static_cast<PokerAction *>(PokerAction::create(this->processControl));
		}else{
			pokerAction = static_cast<AiPokerAction *>(AiPokerAction::create(this->processControl));
		}
        this->addChild(pokerAction);
        
        pokerAction->raisePlayer = CC_CALLBACK_0(LoopPokerAction::setLastRaisePlayer, this);
        pokerAction->endFunc = CC_CALLBACK_0(LoopPokerAction::BetEnd,this);
        
        //是否是 Check  还是 Bet
        if (processControl->getLastBetScore() == 0) {
            pokerAction->Check();
        }else{
            pokerAction->Bet();
        }
	}
}

bool LoopPokerAction::init(Player* betingPlayer){
	return true;
}

void LoopPokerAction::setLastRaisePlayer(){
    TP::log("LoopPokerAction::setLastRaisePlayer",betingPlayer);
    
	this->lastRaisePlayer = processControl->PrePlayer(this->betingPlayer->getPlayerIndex());
    
	//流程结束玩家
	this->lastPlayer = this->lastRaisePlayer;
}



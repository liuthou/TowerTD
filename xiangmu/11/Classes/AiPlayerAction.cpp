//
//  AiPlayerAction.cpp
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-13.
//
//

#include "AiPlayerAction.h"

#include "Global.h"

#include "BetTimePokerAnimation.h"

using namespace TexasPoker;

bool AiPokerAction::init(){
    return true;
}

AiPokerAction* AiPokerAction::create(ProcessControl * processControl){
	AiPokerAction *pRet = new AiPokerAction();
    TP::log("AiPokerAction *pRet = new AiPokerAction()");
    
	if (pRet && pRet->init()) {
		pRet->autorelease();
        
		pRet->processControl = processControl;
        
        pRet->initData();
        
        TP::log("AiPokerAction::create lastBetScore: %d ", pRet->processControl->getLastBetScore());
        
		return pRet;
	} else{
		delete pRet;
		pRet = NULL;
		return NULL;
	} 
}

/**押注bet(); 弃牌,跟注,加注
    1. 设置时间调度器: betTime ,做进度条动画，时间结束之后回调: 弃牌

    为一个玩家创建一个下注动作
    player = loopPokerAction->getBetingPlayer();
     
    三个功能:
    1. 弃牌
    this->Fold();
    2. 跟注
    this->Call();
    3. 加注
    this->Raise();
*/
void AiPokerAction::Bet(){
    TP::log("AiPokerAction::Bet");
    
    if (betingPlayer->getPlayerGameState() == ePlayerGameState::FOLD) {
        End();
        return;
    }
    
    topLabel->setString(languagePokerAction.at("Bet").asString());

    
    if (betingPlayer->getScore() < processControl->getLastBetScore()) {
        log("betingPlayer->getScore() %d",betingPlayer->getScore());
        
        delayRun(CC_CALLBACK_0(PokerAction::AllIN, this));
        
        return;
    }
    
    srand((int)clock());
	
    // AI的智能
    int a = rand() % 10 + 1;
    switch (a){
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7: delayRun(CC_CALLBACK_0(PokerAction::Call, this)); break;
        case 8:
        case 9: delayRun(CC_CALLBACK_0(AiPokerAction::onRaise, this)); break;
        case 10: delayRun(CC_CALLBACK_0(PokerAction::Fold, this)); break;
    }
}

/**回调加注*/
void AiPokerAction::onRaise(){
    TP::log("AiPokerAction::onRaise");
    
	//如果玩家的钱少于上家下注的钱，则直接进行AllIN操作，否则，进行加注操作
	if (betingPlayer->getScore()  < processControl->getLastBetScore() *2 ){
        delayRun(CC_CALLBACK_0(PokerAction::AllIN, this)); 
	}
	else
	{
		/**-----------------------------------------
		1.加注动画，暂时用延时动画替代
		2. 加注金额不能大于场内任何一人的最大携带金额
		//-------------------. 每轮每人只能加注最多两次,如果超过2次自动跳过
		3.加注金额为自身所有携带积分(可能全部),提示AllIN（动画，音效）
		4.能够加注的条件是携带筹码必须大于上家下注金额
		----------------------------------------*/
        
        int raiseScore = processControl->getLastBetScore() == 0  ?
            RoomScoreMin : processControl->getLastBetScore() * 2;
		Raise(raiseScore);
	}
}

void AiPokerAction::Check(){
    TP::log("AiPokerAction::Check");
    
    if (betingPlayer->getPlayerGameState() == ePlayerGameState::FOLD) {
        log("AiPokerAction::Check PlayerGameState == GameState::FOLD endFunc Player:%p \n",betingPlayer);
        End();
        return;
    }
    
    topLabel->setString(languagePokerAction.at("Check").asString());

    
    //如果是第二轮 - 第四轮的小盲注
    auto nowProcessState = processControl->getNowProcessState();
    
    if (nowProcessState == ProcessControl::ProcessState::FlopLittleBlindCheck
        || nowProcessState == ProcessControl::ProcessState::TurnLittleBlindCheck
        || nowProcessState == ProcessControl::ProcessState::RiverLittleBlindCheck
        ) {
        
        srand((int)clock());
        
        // 看牌， 弃牌
        int a1 = rand() % 10 + 1;
        
        log("nowProcessState = processControl->getNowProcessState(); a1 : %d",a1);

        switch (a1){
            case 1:
            case 2:
            case 3: Fold(); break;
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10: Pass(); break;
//                case 10: Fold(); break;
        }
        return;
        
    }
    
    /**
     *  看牌阶段, 是否同意上家的看牌
     *  1. 如果同意 继续看牌
     *  2. 不同意 下注
     */
    if (betingPlayer->getScore() > 0 ) {
        srand((int)clock());
        
        // 看牌， 下注
        int a1 = rand() % 10 + 1;
        switch (a1){
            case 1:
            case 2:
            case 3: delayRun(CC_CALLBACK_0(PokerAction::Pass, this)); break;
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10: delayRun(CC_CALLBACK_0(AiPokerAction::onRaise, this)); break;
        }
        return;
    }else{
        delayRun(CC_CALLBACK_0(PokerAction::Pass, this)); 
    }
    
}


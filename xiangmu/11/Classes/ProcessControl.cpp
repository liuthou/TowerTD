//
//  ProcessControl.cpp
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-13.
//
//

#include "ProcessControl.h"

#include "Room.h"
#include "LoopPokerAction.h"
#include "Function.h"
#include "PokerAction.h"
#include "AiPlayerAction.h"
#include "ChipPoolControl.h"
#include "Function.h"
#include "Global.h"

/**
 *  以下引入pokerAnimation
 */
#include "DealingPokersAnimation.h"
#include "VictoryAnimation.h"

using namespace TexasPoker;

ProcessControl * ProcessControl::create(Room *room){
    ProcessControl *pRet = new ProcessControl();
    if (pRet && pRet->init(room)){
        pRet->autorelease();
        
        return pRet;
    }else{
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool ProcessControl::init(Room *room){
    log("ProcessControl::init\n");
    
	this->room = room;
    
    this->nowProcessState = ProcessState::Null;
    
	this->DealerPlayerChair = room->getDealerPlayerChair();
	this->ChairsAtProcess = room->getChairs_Players();
	this->DealerPlayer = ChairsAtProcess.at(DealerPlayerChair);
	
    this->lastBetScore = 0;
    
    this->chipPoolControl = ChipPoolControl::create();
    this->addChild(this->chipPoolControl);
    
    this->nowRiverPokerNumber = 0;
    
    return true;
}

//索引链表
void ProcessControl::Index(){
    switch (nowProcessState) {
        case ProcessState::Null:
            Start();
            break;
        case ProcessState::Start:
            Perflop();
            break;
        case ProcessState::Perflop:
            PerflopLittleBlind();
            break;
        case ProcessState::PerflopLittleBlind:
            PerflopBigBlind();
            break;
        case ProcessState::PerflopBigBlind:
            PerflopLoopPokerAction();
            break;
        case ProcessState::PerflopLoopPokerAction:
            PerflopEnd();
            break;
        case ProcessState::PerflopEnd:
            Flop();
            break;
        case ProcessState::Flop:
            FlopLittleBlindCheck();
            break;
        case ProcessState::FlopLittleBlindCheck:
            FlopLoopPokerAction();
            break;
        case ProcessState::FlopLoopPokerAction:
            FlopEnd();
            break;
        case ProcessState::FlopEnd:
            Turn();
            break;
        case ProcessState::Turn:
            TurnLittleBlindCheck();
            break;
        case ProcessState::TurnLittleBlindCheck:
            TurnLoopPokerAction();
            break;
        case ProcessState::TurnLoopPokerAction:
            TurnEnd();
            break;
        case ProcessState::TurnEnd:
            River();
            break;
        case ProcessState::River:
            RiverLittleBlindCheck();
            break;
        case ProcessState::RiverLittleBlindCheck:
            RiverLoopPokerAction();
            break;
        case ProcessState::RiverLoopPokerAction:
            RiverEnd();
            break;
        case ProcessState::RiverEnd:
            log("ProcessControl::Index");
            Clear();
            break;
        default:
            break;
    }
    
}

//根据当前玩家的 playerIndex, 返回他的下家
Player * ProcessControl::NextPlayer(int playerIndex){
	//判断当前玩家是否是数组最后一个.........，如果是，下一个玩家就是数组第一个
	playerIndex++;
	// 超过9 就置为1
	
    if (playerIndex > 9){
		playerIndex = 1;
	}
    
	for (; playerIndex <= 9; playerIndex++)
	{
        Player * nextPlayer = ChairsAtProcess.at(playerIndex);
		if (nextPlayer != NULL && nextPlayer->getPlayerGameState() != ePlayerGameState::FOLD) {
            return nextPlayer;
            break;
		}
        
        if (playerIndex == 9){
            playerIndex = 1;
        }
	}
    CCASSERT(1 == 2, " nextplay not be nullptr");
    return nullptr;
}

//根据当前玩家的 playerIndex, 返回他的上家
Player* ProcessControl::PrePlayer(int playerIndex){
	
	//传来的是当前玩家，所以--就代表上一个玩家
	playerIndex--;
    
	//判断当前玩家是否是第一个，如果是第一个，那么他的上家就是最后一个
	if (playerIndex == 0){
		playerIndex = 9;
	}
    
	//逆序寻找上一个玩家
	for (; playerIndex >=0; playerIndex--){
		Player* perPlayer = ChairsAtProcess.at(playerIndex);
		if (perPlayer != NULL && perPlayer->getPlayerGameState() != ePlayerGameState::FOLD){
			return perPlayer;
		}
        
        if (playerIndex == 0){
            playerIndex = 9;
        }
	}
    CCASSERT(1 == 2, " perPlayer not be nullptr");
	return nullptr;
}

// Start : Start
void ProcessControl::Start(){
    
    //1. 设置当前状态
    nowProcessState = ProcessState::Start;
    
    //2. 获取椅子上的玩家
    ChairsAtProcess = room->getChairs_Players();
    
    //3.是否设置庄家
    bool needDealerPlayer = true;
    
	// 有庄家椅子
	for (int i = 1; i <=9; i++)
	{
		Player * player = ChairsAtProcess.at(i);
        
		if (player == NULL) {
			continue;
		}
		//设置玩家游戏状态
		player->setGameState(true);
		//3. 设置庄家
		int playerIndex = player->getPlayerIndex();
		if (playerIndex >= DealerPlayerChair  && needDealerPlayer) {
			this->SetDealerPlayer(playerIndex);
			needDealerPlayer = false;
		}
	}
    
    
	// 创建一副洗好的牌
	newWholePokers();
    
    //发牌
    DealingPokers();
}


// Start : 设置庄家
void ProcessControl::SetDealerPlayer(int chairNumber){
	DealerPlayer = ChairsAtProcess.at(chairNumber);
    
    /**
     *  设置庄家椅子上的小图标
     */
    
    Sprite * dealerSprite = static_cast<Sprite *>(this->room->getChildByName("dealerSprite"));
    if(dealerSprite == nullptr){
        dealerSprite = Sprite::createWithSpriteFrameName("user_d.png");
        room->addChild(dealerSprite);
    }
    auto playerItem = room->getPlayerItemByChairNumber(chairNumber);
    float _x = playerItem->getContentSize().width;
    float _y = playerItem->getContentSize().height;
    
    dealerSprite->setPosition(playerItem->getPosition());
    dealerSprite->setPositionY(dealerSprite->getPositionY() - _y/2);
    
    if(playerItem->getPositionX() <500){
        dealerSprite->setPositionX(dealerSprite->getPositionX() + _x/2);
    }else{
        dealerSprite->setPositionX(dealerSprite->getPositionX() - _x/2);
    }
    
}


// Start : 发牌
void ProcessControl::DealingPokers(){
    
    auto chairs = ChairsAtProcess;
    
	/* 发牌, 从小盲注开始发牌, 根据庄家椅子开始找小盲注, 超过9 就置为0,继续直到庄家停止*/
	// 找到小盲注 和 大盲注
	littleBlindsPlayer = this->NextPlayer(DealerPlayerChair);
	BigBlindsPlayer = this->NextPlayer(littleBlindsPlayer->getPlayerIndex());
    
	// 扑克的迭代器
	//auto it_poker = wholePokers.begin();
    
	// 发手牌, 从小盲注开始，连续发牌两圈
	for (int i = 0; i<2; i++)
	{
		int index = littleBlindsPlayer->getPlayerIndex();
		for(int j = 1 ; j <= 9; j++){
			Player* player = chairs.at(index);
            
			// 判断椅子上是否有玩家
			if (player != NULL) {
                player->getPoker_Array()->setHandVector(wholePokers.back());
                wholePokers.popBack();
			}
			index++;
			if (index > 9){
				index = 1;
			}
		}
	}
    
    DealingPokersAnimationIndex = littleBlindsPlayer->getPlayerIndex();
    DealingPokersAnimationLoopNumber = 1;
    DealingPokersAnimation();
    
}

void ProcessControl::DealingPokersAnimation(){
    
    if (DealingPokersAnimationLoopNumber != 3 ){
        
        auto dealingPokersAnimation = DealingPokersAnimation::create(this);
        
        dealingPokersAnimation->setEndFunc(CC_CALLBACK_0(ProcessControl::DealingPokersAnimation, this));
        dealingPokersAnimation->setPosition(Vec2::ZERO);
        this->addChild(dealingPokersAnimation);
        
        dealingPokersAnimation->dealing(DealingPokersAnimationIndex);
        DealingPokersAnimationIndex++;
        
        if( DealingPokersAnimationIndex == littleBlindsPlayer->getPlayerIndex() ){
            DealingPokersAnimationLoopNumber++;
            DealingPokersAnimationIndex = littleBlindsPlayer->getPlayerIndex();
        }
        
        if (DealingPokersAnimationIndex > 9){
            DealingPokersAnimationIndex = 1;
        }
    }else{
        Index();
    }
}

// Start : 创建一副洗好的牌
void ProcessControl::newWholePokers(){
	// 创建一副牌
	for (int j = 1; j<=4; j++)
	{
		for (int i=2; i<= 14; i++)
		{
			Poker *p = Poker::create(Function::getPokerColor(j), i);
			wholePokers.pushBack(p);
		}
	}
    
	// 洗牌
    TexasPoker::Function::randomVector(wholePokers);
}


// Perflop : Perflop
void ProcessControl::Perflop(){
	//1. 设置当前状态
	nowProcessState = ProcessState::Perflop;
    
	// 调用索引
	Index();
}

// Perflop : Perflop小盲注
void ProcessControl::PerflopLittleBlind(){
	/**控制小盲注做下注动画，并从房间携带金额里减去下注金额*/
	//1. 设置当前状态，小盲注置成lastPlayer
	nowProcessState = ProcessState::PerflopLittleBlind;
	
    //2. 设置当前下注玩家
    this->setBetingPlayer(littleBlindsPlayer);
    
	/**获取当前玩家类型，如果是Normal，就执行真实玩家的小盲注，如果是AI,就执行电脑玩家小盲注*/
    PokerAction * _pockerAction = nullptr;
	if (BetingPlayer->getPlayerType() == ePlayerType::NORMAL)
	{
		//normalPlayer小盲注下注动画, 直接抛出,最低筹码
		_pockerAction = PokerAction::create(this);
	}else{
		_pockerAction = (AiPokerAction *)AiPokerAction::create(this);
	}
    
    this->addChild(_pockerAction);
    
    _pockerAction->raisePlayer = nullptr;
    
    _pockerAction->endFunc = CC_CALLBACK_0(ProcessControl::Index, this);
    
    _pockerAction->LittleBlinds();
}


// Perflop : Perflop大盲注
void ProcessControl::PerflopBigBlind(){
	//1. 设置当前状态
	nowProcessState = ProcessState::PerflopBigBlind;
    
	/**
     *  2. 设置当前下注玩家
     */
    this->setBetingPlayer(BigBlindsPlayer);
    
	/**获取当前玩家类型，如果是Normal，就执行真实玩家的大盲注，如果是AI,就执行电脑玩家大盲注*/
    PokerAction * _pockerAction = nullptr;
	if (BetingPlayer->getPlayerType() == ePlayerType::NORMAL)
	{
		//normalPlayer大盲注下注动画, 直接抛出,最低筹码
		_pockerAction = PokerAction::create(this);
	}else{
		/**AI大盲注下注动画，直接直接抛出,最低筹码*/
		_pockerAction = (AiPokerAction*)AiPokerAction::create(this);
	}
    this->addChild(_pockerAction);
    
    _pockerAction->raisePlayer = nullptr;
    
    _pockerAction->endFunc = CC_CALLBACK_0(ProcessControl::Index, this);
    
    _pockerAction->BigBlinds();
}


// Perflop : Perflop大盲注之后的 LoopPokerAction
void ProcessControl::PerflopLoopPokerAction(){
	//1. 设置当前状态
	nowProcessState = ProcessState::PerflopLoopPokerAction;
    
	//2:下家下注动画, 最低筹码*2,进入第一轮循环流程
	auto _loopAction = LoopPokerAction::create(this);
    this->addChild(_loopAction);
    
	_loopAction->endFunc = CC_CALLBACK_0(ProcessControl::Index,this);
	_loopAction->BetEnd();
}

// Perflop : Perflop的结束
void ProcessControl::PerflopEnd(){
	//1. 设置当前状态
	nowProcessState = ProcessState::PerflopEnd;
    
    //2. 清理最后一次下注金额
    this->setLastBetScore(0);
    
	// 清理桌上的 tempScore， 合到一个池中
    chipPoolControl->pushBegin();
    for (auto it : ChairsAtProcess) {
        chipPoolControl->pushScore(it.second);
    }
    chipPoolControl->pushEnd();
    
    flushPlayerTempScoreAndPlayerItemLabel();
    
    TP::log("++++++++++++++++++++++++ (1) OVER! ++++++++++++++++++++++++");
	
    // 延时调用Index
    delayTimeIndex(1.0f);
}

// Flop : Flop的开始
void ProcessControl::Flop(){
	//1. 设置当前状态
	nowProcessState = ProcessState::Flop;
    
    //亮出 3张 河牌
    for(int i =1 ; i<=3; i++){
        riverPokers.pushBack(wholePokers.back());
        wholePokers.popBack();
    }
    
    
	// 调用第二轮开始,翻3张
    nowRiverPokerNumber = 0;
    turnRiverPoker();
}

void ProcessControl::FlopLittleBlindCheck(){
	//1. 设置当前状态
	nowProcessState = ProcessState::FlopLittleBlindCheck;
    
    TP::log("ProcessControl::FlopLittleBlindCheck littleBlindsPlayer : %p",littleBlindsPlayer);
    
	//2. 设置当前下注玩家; 要在小盲注中途离去时，重新设置小盲注
    this->setBetingPlayer(littleBlindsPlayer);
    
	/**获取当前玩家类型，如果是Normal，就执行真实玩家的小盲注，如果是AI,就执行电脑玩家小盲注*/
    PokerAction * _pockerAction = nullptr;
	if (BetingPlayer->getPlayerType() == ePlayerType::NORMAL)
	{
		//normalPlayer小盲注下注动画, 直接抛出,最低筹码
		_pockerAction = PokerAction::create(this);
	}else{
		/**AI小盲注下注动画，直接直接抛出,最低筹码*/
		_pockerAction = AiPokerAction::create(this);
	}
    this->addChild(_pockerAction);
    
    _pockerAction->raisePlayer = nullptr;
    
    _pockerAction->endFunc = CC_CALLBACK_0(ProcessControl::Index, this);
    
    _pockerAction->Check();
}

void ProcessControl::FlopLoopPokerAction(){
	//1. 设置当前状态
	nowProcessState = ProcessState::FlopLoopPokerAction;
    
	//2. 进行第二轮，桌面亮前三张河牌
	auto _loopAction = LoopPokerAction::create(this);
    this->addChild(_loopAction);
    
	_loopAction->endFunc = CC_CALLBACK_0(ProcessControl::Index,this);
	_loopAction->BetEnd();
    
	// 调用索引
	//Index();
}

void ProcessControl::FlopEnd(){
	//1. 设置当前状态
	nowProcessState = ProcessState::FlopEnd;
    
    //2. 清理最后一次下注金额
    this->setLastBetScore(0);
    
	// 未实现:  3. 清理桌上的 tempScore， 合到一个池中
    chipPoolControl->pushBegin();
    for (auto it : ChairsAtProcess) {
        chipPoolControl->pushScore(it.second);
    }
    chipPoolControl->pushEnd();
    
    flushPlayerTempScoreAndPlayerItemLabel();
    
    TP::log("++++++++++++++++++++++++ (2) OVER! ++++++++++++++++++++++++");
    
	// 延时调用Index
    delayTimeIndex(1.0f);
}

void ProcessControl::Turn(){
    log("ProcessControl::Turn");
	//1. 设置当前状态
	nowProcessState = ProcessState::Turn;
    
    //2. 翻第四张河牌
    riverPokers.pushBack(wholePokers.back());
    wholePokers.popBack();
    
	
    // 调用第三轮,翻第四章
    nowRiverPokerNumber = 3;
    turnRiverPoker();
}

void ProcessControl::TurnLittleBlindCheck(){
	//1. 设置当前状态
	nowProcessState = ProcessState::TurnLittleBlindCheck;
    
	//2. 设置当前下注玩家; 要在小盲注中途离去时，重新设置小盲注
	BetingPlayer =  littleBlindsPlayer;
    
	/**获取当前玩家类型，如果是Normal，就执行真实玩家的小盲注，如果是AI,就执行电脑玩家小盲注*/
    PokerAction *_pockerAction = nullptr;
	if (BetingPlayer->getPlayerType() == ePlayerType::NORMAL)
	{
		//normalPlayer小盲注下注动画, 直接抛出,最低筹码
		_pockerAction = PokerAction::create(this);
	}else
	{
		/**AI小盲注下注动画，直接直接抛出,最低筹码*/
		_pockerAction = AiPokerAction::create(this);
	}
    _pockerAction->raisePlayer = nullptr;
    
    _pockerAction->endFunc = CC_CALLBACK_0(ProcessControl::Index, this);
    
    _pockerAction->Check();
}

void ProcessControl::TurnLoopPokerAction(){
	//1. 设置当前状态
	nowProcessState = ProcessState::TurnLoopPokerAction;
    
	//2. 进行第三轮，桌面亮第四张河牌
	auto _loopAction = LoopPokerAction::create(this);
    this->addChild(_loopAction);
    
	_loopAction->endFunc = CC_CALLBACK_0(ProcessControl::Index,this);
	_loopAction->BetEnd();
    
	// 调用索引
	//Index();
}

void ProcessControl::TurnEnd(){
	//1. 设置当前状态
	nowProcessState = ProcessState::TurnEnd;
    
    //2. 清理最后一次下注金额
    this->setLastBetScore(0);
    
	// 未实现:  3. 清理桌上的 tempScore， 合到一个池中
    chipPoolControl->pushBegin();
    for (auto it : ChairsAtProcess) {
        chipPoolControl->pushScore(it.second);
    }
    chipPoolControl->pushEnd();
    
    flushPlayerTempScoreAndPlayerItemLabel();
    
    TP::log("++++++++++++++++++++++++ (3) OVER! ++++++++++++++++++++++++");
    
	// 延时调用Index
    delayTimeIndex(1.0f);
}

void ProcessControl::River(){
	//1. 设置当前状态
	nowProcessState = ProcessState::River;
    
    //2. 翻第五张河牌
    riverPokers.pushBack(wholePokers.back());
    wholePokers.popBack();
    
    for(auto it : riverPokers){
        log("riverPokers %d",it->getNo());
    }
    
    // 调用第三轮开始,翻第五张
    nowRiverPokerNumber = 4;
    turnRiverPoker();
}

void ProcessControl::RiverLittleBlindCheck(){
	//1. 设置当前状态
	nowProcessState = ProcessState::RiverLittleBlindCheck;
    
	//2. 设置当前下注玩家; 要在小盲注中途离去时，重新设置小盲注
    this->setBetingPlayer(littleBlindsPlayer);
    
	/**获取当前玩家类型，如果是Normal，就执行真实玩家的小盲注，如果是AI,就执行电脑玩家小盲注*/
    PokerAction *_pockerAction = nullptr;
	if (BetingPlayer->getPlayerType() == ePlayerType::NORMAL)
	{
		//normalPlayer小盲注下注动画, 直接抛出,最低筹码
		_pockerAction = PokerAction::create(this);
	}else
	{
		/**AI小盲注下注动画，直接直接抛出,最低筹码*/
		_pockerAction = AiPokerAction::create(this);
	}
    this->addChild(_pockerAction);
    
    _pockerAction->raisePlayer = nullptr;
    
    _pockerAction->endFunc = CC_CALLBACK_0(ProcessControl::Index, this);
    
    _pockerAction->Check();
}


void ProcessControl::RiverLoopPokerAction(){
	//1. 设置当前状态
	nowProcessState = ProcessState::RiverLoopPokerAction;
    
	//2. 进行第四轮，桌面有五张河牌
	auto _loopAction = LoopPokerAction::create(this);
    this->addChild(_loopAction);
    
	_loopAction->endFunc = CC_CALLBACK_0(ProcessControl::Index,this);
	_loopAction->BetEnd();
    
	// 调用索引
	//Index();
}


void ProcessControl::RiverEnd(){
	//1. 设置当前状态
	nowProcessState = ProcessState::RiverEnd;
    
    //2. 清理最后一次下注金额
    this->setLastBetScore(0);
    
	// 未实现:  3. 清理桌上的 tempScore， 合到一个池中
    chipPoolControl->pushBegin();
    for (auto it : ChairsAtProcess) {
        chipPoolControl->pushScore(it.second);
    }
    chipPoolControl->pushEnd();
    
    flushPlayerTempScoreAndPlayerItemLabel();
    
    TP::log("++++++++++++++++++++++++ (4) OVER! ++++++++++++++++++++++++");
    
	// 延时调用Index
    delayTimeIndex(1.0f);
}


void ProcessControl::Clear(){
	TP::log("===========i am clear ============");
	
    
	//1. 倒序遍历底池，拿到每一个底池的 筹码和参与的玩家
	//2. 根据 参与玩家，返回赢家
	//3. 给玩家分钱，使玩家的 Room内的携带筹码 增加
	//4. 执行分钱的动画
	//5. 释放应该释放的资源
    
	Vector<ChipPool * > vChipPools = this->chipPoolControl->getChipPoolVector();
    
    log("vChipPools.size() %zd",vChipPools.size());
    
    /**
     *  设置每个玩家的牌型
     */
    SetPlayerPokerMethod();
    
	for (int i = (int)vChipPools.size()-1; i>=0; i--){
		auto chipPool = vChipPools.at(i);
		auto totalScore = chipPool->totalScore;
		auto players = chipPool->players;
		
        log("chipPool: totalScore:%d, players:%zd",totalScore,players.size());
        
		// 获得某个池的赢家
		Vector<Player *> winners = Function::getWinners(players);
        
        //执行获胜动画
        for(auto it: winners){
            auto victoryAnimation = VictoryAnimation::create();
            victoryAnimation->setPosition(568, 320);
            room->addChild(victoryAnimation,10);
            //玩家胜利动画
            victoryAnimation->play(it->getPoker_Array()->getPoker_Method());
            
            //获胜玩家高亮
            auto hightLight = Sprite::createWithSpriteFrameName("user_4.png");
            auto playerItem = this->getRoom()->getPlayerItemByChairNumber(it->getPlayerIndex());
            
            float x = hightLight->getContentSize().width;
            float y = hightLight->getContentSize().height;
            
            hightLight->setPositionX(x/2 -10);
            hightLight->setPositionY(y/2 -10);
            
            playerItem->addChild(hightLight);
        }
        
		// 分钱
		Function::winnersGetScore(totalScore, winners);
        
		// 执行分钱动画
        
	}
}

void ProcessControl::SetPlayerPokerMethod(){
    log("ProcessControl::SetPlayerPokerMethod");
    
    for (auto it : ChairsAtProcess) {
        auto playerSecond = it.second;
        if(playerSecond->getPlayerGameState() != ePlayerGameState::FOLD){
            playerSecond->getPoker_Array()->setRiverVector(riverPokers);
            PokerMethod method = Function::getPokerMethodForHanderAndRiver(playerSecond);
            
            auto playerItem = room->getPlayerItemByChairNumber(playerSecond->getPlayerIndex());
            auto playerItemTopLabel =
            static_cast<Label *>( playerItem->getChildByName("topLabel") );
            playerItemTopLabel->setString(Function::getStringForPokerMethod(method));
        }
    }
}

void ProcessControl::addPlayerTempScore(Player *player,int tempScore){
    player->addTempScore(tempScore);
    this->setLastBetScore(tempScore);
    
    flushPlayerTempScore(player,nullptr);
}

void ProcessControl::flushPlayerTempScoreAndPlayerItemLabel(){
    for (auto it : ChairsAtProcess) {
        auto player = it.second;
        
        auto playerItem = room->getPlayerItemByChairNumber(player->getPlayerIndex());
        
        flushPlayerTempScore(player, playerItem );
        flushPlayerTopLabel(player, playerItem );
    }
    
    
}

void ProcessControl::flushPlayerTopLabel(Player * player,MenuItemSprite *_playerItem=nullptr){
    MenuItemSprite * playerItem =  nullptr;
    
    if(_playerItem == nullptr){
        playerItem = room->getPlayerItemByChairNumber(player->getPlayerIndex());
    }else{
        playerItem = _playerItem;
    }
    
    auto label =
    static_cast<Label *>( playerItem->getChildByName("topLabel"));
    
    label->setString(player->getName());
    
}

void ProcessControl::flushPlayerTempScore(Player * player,MenuItemSprite *_playerItem=nullptr){
    MenuItemSprite * playerItem =  nullptr;
    if(_playerItem == nullptr){
        playerItem = room->getPlayerItemByChairNumber(player->getPlayerIndex());
    }else{
        playerItem = _playerItem;
    }
    
    auto label =
    static_cast<Label *>( playerItem->getChildByName("bottomLabel"));
    label->setString( Function::getFormatScore(player->getScore()) );
    
    auto label2 =
    static_cast<Label *>( playerItem->getChildByName("tempScoreLabel") );
    label2->setString( Function::getFormatScore(player->getTempScore()) );
    label2->setVisible(false);
    
    auto chipPoolSprite =
    static_cast<Sprite *>( playerItem->getChildByName("chipPool") );
    chipPoolSprite->setVisible(false);
    
}


/**房间(用来拿到房间中的庄家椅子号)*/
Room * ProcessControl::getRoom(){
    return room;
}

void ProcessControl::turnRiverPoker(){
    log("ProcessControl::turnRiverPoker %d",nowRiverPokerNumber);
    
    //1. 动画
    //1.1 添加临时精灵
    //1.2 执行动画
    //2. 回调
    //3. 添加扑克
    //4. 判断结束
    
    Sprite * tempSprite = Sprite::createWithSpriteFrameName("poker_bg_2.png");
    
    if(nowRiverPokerNumber == 0){
        tempSprite->setPosition(390, 345);
        tempSprite->setName("river1");
        room->addChild(tempSprite,1);
        
        nowRiverPokerNumber = 1;
        
    }else if(nowRiverPokerNumber ==1){
        tempSprite->setPosition(475, 345);
        tempSprite->setName("river2");
        room->addChild(tempSprite,1);
        
        nowRiverPokerNumber = 2;
        
    }else if(nowRiverPokerNumber == 2){
        tempSprite->setPosition(568, 345);
        tempSprite->setName("river3");
        room->addChild(tempSprite,1);
        
        nowRiverPokerNumber = 3;
        
    }else if(nowRiverPokerNumber == 3){
        tempSprite->setPosition(661, 345);
        tempSprite->setName("river4");
        room->addChild(tempSprite,1);
        
        nowRiverPokerNumber = 4;
        
    }else if(nowRiverPokerNumber == 4){
        tempSprite->setPosition(754, 345);
        tempSprite->setName("river5");
        room->addChild(tempSprite,1);
        
        nowRiverPokerNumber = 5;
        
    }
    
    if(tempSprite != nullptr){
        auto animation = Animation::create();
        for(int i = 1; i<=5; i++){
            animation->addSpriteFrame(
                                      SpriteFrameCache::getInstance()->getSpriteFrameByName(
                                                                                            StringUtils::format("poker_fanpai_%d.png",i)
                                                                                            ));
        }
        animation->setDelayPerUnit(0.1);
        animation->setLoops(1);
        
        auto callFunc = CallFunc::create([this](){
            addRiverPoker();
        });
        
        tempSprite->runAction(
                              Sequence::create(Animate::create(animation),callFunc, NULL)
                              );
    }else{
    }
    
}

void ProcessControl::addRiverPoker(){
    log("ProcessControl::addRiverPoker");
    
    auto preSprite =
    static_cast<Sprite *>( this->room->getChildByName(
                                                      StringUtils::format("river%d",nowRiverPokerNumber)) );
    
    log("nowRiverPokerNumber : %d  preSprite: %p\n",nowRiverPokerNumber,preSprite);
    CCASSERT(preSprite != nullptr, "preSprite not nullptr");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AUDIO/fapai2.mp3");
    
    auto _riverPoker = riverPokers.at(nowRiverPokerNumber-1);
    _riverPoker->setPosition(preSprite->getPosition());
    
    room->addChild(_riverPoker,1);
    room->removeChild(preSprite);
    
    if (nowProcessState == ProcessState::Flop) {
        
        if (nowRiverPokerNumber < 3) {
            turnRiverPoker();
        }else{
            SetPlayerPokerMethod();
            Index();
        }
        
    }else{
        SetPlayerPokerMethod();
        Index();
    }
}

void ProcessControl::delayTimeIndex(float time){
    auto callFunc = CallFunc::create(CC_CALLBACK_0(ProcessControl::Index, this));
    auto delayTime = DelayTime::create(time);
    
    this->runAction(Sequence::create(delayTime,callFunc, NULL));
}

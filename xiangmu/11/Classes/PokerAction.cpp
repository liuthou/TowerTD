//
//  PokerAction.cpp
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-13.
//
//

#include "PokerAction.h"
#include "ProcessControl.h"

#include "Global.h"

#include "FoldPokerAnimation.h"

bool PokerAction::init(){
    TP::log("PokerAction::init");
    if(!Layer::init()){
        return false;
    }
	return true;
}

PokerAction* PokerAction::create(ProcessControl * processControl){
	PokerAction *pRet = new PokerAction();
        
	if (pRet && pRet->init()) {
        pRet->autorelease();
        pRet->processControl = processControl;
        
        pRet->initData();
        
        return pRet;
	} else{
        delete pRet;
        pRet = NULL; 
        return NULL; 
	} 
}

void PokerAction::addTimer(){
    log("PokerAction::addTimer");
    
    auto playIndex = this->betingPlayer->getPlayerIndex();

    //创建一个倒计时框
    betTimePokerAnimation = BetTimePokerAnimation::create(processControl);
    betTimePokerAnimation->setEndFunc(CC_CALLBACK_0(PokerAction::Fold, this));
    
    this->addChild(betTimePokerAnimation);
    
    betTimePokerAnimation->bettingTime(playIndex);
    
}

void PokerAction::initData(){
    
    /**
     *  当前下注玩家
     */
    this->betingPlayer = processControl->getBetingPlayer();
    
    this->playerItem = processControl->getRoom()->getPlayerItemByChairNumber(
                       this->betingPlayer->getPlayerIndex());
    
    this->topLabel =static_cast<Label *>( this->playerItem->getChildByName("topLabel") );
    
    this->languagePokerAction = Config::LANGUAGE::getInstance()->AT("PokerAction").asValueMap();
    
    
    //添加倒计时框
    this->addTimer();
    
    /**获得最多可携带最高金额*/
    this->RoomScoreMax = processControl->getRoom()->getScoreMax();
    
    /**获得最低下注金额*/
    this->RoomScoreMin = processControl->getRoom()->getScoreMin();
}

/**看牌; 弃牌,看牌,下注
1. 加入时间调度器
2. 弹出选择框
1.1 看牌
this->Pass();
1.2 下注
this->Call();
1.3 弃牌
this->Fold();
*/
void PokerAction::Bet(){
    if (betingPlayer->getPlayerGameState() == ePlayerGameState::FOLD) {
        End();
        return;
    }
    
    topLabel->setString(languagePokerAction.at("Bet").asString());
    
    
	// 弃牌操作精灵
	auto foldSprite = Sprite::create("CloseNormal.png");
	// 跟注操作精灵
	auto callSprite = Sprite::create("CloseNormal.png");
	// 加注操作精灵
	auto raiseSprite = Sprite::create("CloseNormal.png");


	//弃牌按钮
	auto foldMenuItem = MenuItemSprite::create(foldSprite, foldSprite,foldSprite, CC_CALLBACK_1(PokerAction::onFold,this));
	foldMenuItem->setPosition(Vec2(500, 80));

	//跟注按钮
	auto callMenuItem = MenuItemSprite::create(callSprite, callSprite, callSprite, CC_CALLBACK_1(PokerAction::onCall,this)); 
	callMenuItem->setPosition(Vec2(600, 80));

	//加注按钮
	auto raiseMenuItem = MenuItemSprite::create(raiseSprite, raiseSprite, raiseSprite, CC_CALLBACK_1(PokerAction::onRaise,this)); 
	raiseMenuItem->setPosition(Vec2(700, 80));
	int * a =new int(100);
	raiseMenuItem->setUserData(a);

	auto menu = Menu::create(foldMenuItem, callMenuItem, raiseMenuItem, NULL);
	auto scene = Director::getInstance()->getRunningScene();
	scene->addChild(menu);
}

//弃牌: onFold
void PokerAction::onFold(Ref* pSender){
	Fold();
}

//弃牌: Fold
void PokerAction::Fold(){
    TP::log("PokerAction::Fold \n");
    
    topLabel->setString(languagePokerAction.at("Fold").asString());

    
	//玩家状态设为FOLD
    // 提示: 每个FOLD的玩家 都不能参与此局游戏，但是可以进行下一局，这个在 NextPlayer中有控制
	betingPlayer->setPlayerGameState(ePlayerGameState::FOLD);
    
    
    char sex = betingPlayer->getSex();
    if(sex =='m'){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AUDIO/fold_boy.mp3");
    }else if(sex =='f'){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AUDIO/fold_girl.mp3");
    }
    
    //弃牌动画
    auto foldAnimation = FoldPokerAnimation::create(processControl);
    this->addChild(foldAnimation);
    
    foldAnimation->setEndFunc(CC_CALLBACK_0(PokerAction::End, this));
    foldAnimation->fold(betingPlayer->getPlayerIndex());
}

//跟注: onCall
void PokerAction::onCall(Ref*  pSener){
	Call();
}

//跟注: Call
void PokerAction::Call(){
    TP::log("PokerAction::Call; processControl->getLastBetScore() %d \n",processControl->getLastBetScore());
    
    topLabel->setString(languagePokerAction.at("Call").asString());

    
    int needBetScore=0;
    if (processControl->getNowProcessState() == ProcessControl::ProcessState::PerflopLoopPokerAction
        && processControl->getBetingPlayer() == processControl->getLittleBlindsPlayer()
        ) {
        needBetScore = processControl->getLastBetScore() - RoomScoreMin;
        
    }else{
        needBetScore = processControl->getLastBetScore();
        
    }
    
    if (betingPlayer->getScore() < needBetScore) {
        AllIN();
        return;
    }
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AUDIO/chip.mp3");
    
    // 设置 玩家投注到 自己面前桌面上的 钱； 这个要每一轮 清理到 chipPot 中
    processControl->addPlayerTempScore(betingPlayer, needBetScore);
    
    if (processControl->getNowProcessState() == ProcessControl::ProcessState::PerflopLoopPokerAction
        && processControl->getBetingPlayer() == processControl->getLittleBlindsPlayer()
        ) {
        processControl->setLastBetScore(processControl->getLastBetScore() + RoomScoreMin);
    }
    
    char sex = betingPlayer->getSex();
    if(sex =='m'){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AUDIO/call_boy.mp3");
    }else if(sex =='f'){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AUDIO/call_girl.mp3");
    }
    
    EndAndRunBetMoverAnimation();

}

//加注: onRaise
void PokerAction::onRaise(Ref* pSender){
    int chip = processControl->getLastBetScore() + RoomScoreMin;
    
	//如果玩家的钱少于上家下注的钱，则直接进行AllIN操作，否则，进行加注操作
	if (betingPlayer->getScore() <= processControl->getLastBetScore()){
		AllIN();
	}else{
		Raise(chip);
	}
	
}

//加注: Raise
void PokerAction::Raise(int chip){
    TP::log("PokerAction::Raise %d\n",chip);
    
    topLabel->setString(languagePokerAction.at("Raise").asString());

	//抛出筹码的动画
    if(betingPlayer->getScore() < chip){
        AllIN();
        return;
    }
    
	//加注筹码(同上一家一样的)
	processControl->addPlayerTempScore(betingPlayer,chip);
    
	// 设置 loopPokerAction 中的最后加注玩家
    if(raisePlayer != nullptr){
        raisePlayer();
    }

	//将下注的钱存到筹码池里面

    char sex = betingPlayer->getSex();
    if(sex =='m'){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AUDIO/raise_boy.mp3");
    }else if(sex =='f'){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AUDIO/raise_girl.mp3");
    }
    
    EndAndRunBetMoverAnimation();
}

void PokerAction::AllIN(){
    TP::log("PokerAction::AllIN %d \n",betingPlayer->getScore());
    
    topLabel->setString(languagePokerAction.at("AllIN").asString());

    
    //CCASSERT(betingPlayer->getScore() >=0 , "Player Score Must >= 0 ");
    
    /**
     *  AllIN需要重新设置lastBetScore, 先保存一下当前的lastBetScore
     */
    int _lastBetScore = processControl->getLastBetScore();
    
	//将当前所携带的钱全扔入池中
    // 设置 玩家投注到 自己面前桌面上的 钱； 这个要每一轮 清理到 chipPot 中
    processControl->addPlayerTempScore(betingPlayer,betingPlayer->getScore());
    
    processControl->setLastBetScore(_lastBetScore);
    
    
    char sex = betingPlayer->getSex();
    if(sex =='m'){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AUDIO/allin_boy.mp3");
    }else if(sex =='f'){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AUDIO/allin_girl.mp3");
    }
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AUDIO/chipfly.mp3");
    
    EndAndRunBetMoverAnimation();

}

/**看牌; 弃牌,看牌,下注
1. 加入时间调度器
2. 弹出选择框
1.1 看牌
this->Pass();
1.2 下注
this->Call();
1.3 弃牌
*/
void PokerAction::Check(){
    if (betingPlayer->getPlayerGameState() == ePlayerGameState::FOLD) {
        End();
        return;
    }
    
    topLabel->setString(languagePokerAction.at("Check").asString());

    
	// 添加等待时间进度条，超过时间就弃牌
	//this->runAction(DelayTime::create(10.0f));

	auto foldSprite = Sprite::create("CloseNormal.png");
	auto callSprite = Sprite::create("CloseNormal.png");
	auto passSprite = Sprite::create("CloseNormal.png");
    
	auto foldMenuItem = MenuItemSprite::create(foldSprite, foldSprite, foldSprite, CC_CALLBACK_1(PokerAction::onFold,this)); //弃牌按钮
	foldMenuItem->setPosition(Vec2(500, 80));
    
	auto callMenuItem = MenuItemSprite::create(callSprite, callSprite, callSprite, CC_CALLBACK_1(PokerAction::onCall,this)); //看牌按钮
	callMenuItem->setPosition(Vec2(600, 80));
    
	auto passMenuItem = MenuItemSprite::create(passSprite, passSprite, passSprite, CC_CALLBACK_1(PokerAction::onPass,this)); //加注按钮
	passMenuItem->setPosition(Vec2(700, 80));
    
	auto menu = Menu::create(foldMenuItem, callMenuItem, passMenuItem, NULL);
	auto scene = Director::getInstance()->getRunningScene();
	scene->addChild(menu);
}

void PokerAction::onPass(Ref* pSender){
	Pass();
}

void PokerAction::Pass(){
    TP::log("PokerAction::Pass\n");
    
    topLabel->setString(languagePokerAction.at("Pass").asString());

    
	// 看牌没有 动画
	//看牌，将下注金额设为0
	// 设置 玩家投注到 自己面前桌面上的 钱； 这个要每一轮 清理到 chipPot 中
    processControl->addPlayerTempScore(betingPlayer,0);
    
    char sex = betingPlayer->getSex();
    if(sex =='m'){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AUDIO/check_boy.mp3");
    }else if(sex =='f'){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AUDIO/check_girl.mp3");
    }
    
    End();

}

bool PokerAction::LittleBlinds(){
    this->betingPlayer = processControl->getBetingPlayer();
    
    topLabel->setString(languagePokerAction.at("LittleBlinds").asString());

    if (betingPlayer->getScore() >= RoomScoreMin) {
		TP::log("PokerAction::LittleBlinds score can beting: RoomScoreMin =%d", RoomScoreMin);
        
		// 设置 玩家投注到 自己面前桌面上的 钱； 这个要每一轮 清理到 chipPot 中
        processControl->addPlayerTempScore(betingPlayer,RoomScoreMin);

    }else{
        /**房间内金币不足,ALLIN*/
        AllIN();
    }
        
    EndAndRunBetMoverAnimation();
    
	return true;
}

bool PokerAction::BigBlinds(){
    log("PokerAction::BigBlinds");
    
    topLabel->setString(languagePokerAction.at("BigBlinds").asString());

    
    /**
     *  判断当前资金是否可以下注,不然就执行AllIN
     */
	if (betingPlayer->getScore() >= RoomScoreMin*2 ) {
		// 大盲注自动下注，下注金额是房间最低下注金额*2
		// 设置 玩家投注到 自己面前桌面上的 钱； 这个要每一轮 清理到 chipPot 中
        processControl->addPlayerTempScore(betingPlayer,RoomScoreMin*2);
                
        EndAndRunBetMoverAnimation();
        
	}else{
        AllIN();
	}
    
	return true;
}

void PokerAction::End(){
    log("PokerAction::End\n");
    
    auto _endfunc = endFunc;
    
    try{
        this->removeFromParentAndCleanup(true);
    }catch(...){
        ;
    }
    
    _endfunc();
    
}

void PokerAction::EndAndRunBetMoverAnimation(){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AUDIO/chip.mp3");
    
    auto playItem = processControl->getRoom()->getPlayerItemByChairNumber(betingPlayer->getPlayerIndex());
    
    auto chipPoolSprite = static_cast<Sprite *>( playItem->getChildByName("chipPool") );
    auto chipPoolLabel = static_cast<Sprite *>( playItem->getChildByName("tempScoreLabel") );
    
    if (betingPlayer->getTempScore() == 0) {
        chipPoolSprite->setVisible(false);
        chipPoolLabel->setVisible(false);
    }
    
    Sprite * moveChipPool = nullptr;
    auto _tempMoveChipPool = static_cast<Sprite *>( playItem->getChildByName("moveChipPool") );
    if(_tempMoveChipPool !=nullptr){
        moveChipPool = _tempMoveChipPool;
    }else{
        moveChipPool = Sprite::create("UI/chippool_2.png");
        playItem->addChild(moveChipPool);
    }
    
    float x = playItem->getContentSize().width;
    float y = playItem->getContentSize().height; 
    moveChipPool->setPositionX(x/2);
    moveChipPool->setPositionY(y/2);
    moveChipPool->setName("moveChipPool");
    
    
    auto moveTo = MoveTo::create(PokerAction_EndAndRunBetMoverAnimationTime, chipPoolSprite->getPosition() );
    auto showChipPool = CallFunc::create([chipPoolSprite,chipPoolLabel,moveChipPool](){
        chipPoolSprite->setVisible(true);
        chipPoolLabel->setVisible(true);
        moveChipPool->setVisible(false);
    });
    auto callFunc = CallFunc::create(CC_CALLBACK_0(PokerAction::End, this));
    
    moveChipPool->runAction(Sequence::create(moveTo,showChipPool,callFunc, NULL));
    
}

void PokerAction::delayRun(std::function<void()> func){
    log("PokerAction::delayRun(std::function<void()> func) %p",&func);
    
    auto delay = DelayTime::create(PokerAction_AI_DELAY_TIME);
    auto callFunc = CallFunc::create(func);
    this->runAction(Sequence::create(delay, callFunc, NULL));
}



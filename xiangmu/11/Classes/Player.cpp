//
//  Player.cpp
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-13.
//
//

#include "Player.h"
#include "Function.h"
#include "Poker.h"

using namespace TexasPoker;


bool Player::init(ePlayerGameState playerGameState, int _id, std::string name, char sex,
				  int totalScore, int score)
{
	this->playerGameState = playerGameState;
	this->id = _id;
	this->name = name;
	this->sex = sex;
	this->totalScore = totalScore;
	this->score = score;
	this->tempScore = 0;
    
	// 实例化 手牌 和 河牌 的 PokerArray
	this->poker_Array = PokerArray::create();
    
	return true;
}

// 增加玩家的房间内携带积分
void Player::plusRoomScore(int _score){
	this->score += _score;
}

// 减去玩家的房间内携带积分
void Player::subRoomScore(int _score){
	this->score -= _score;
    CCASSERT(this->score>=0, " Player Score Must >= 0 ");
}

// 玩家清除手牌
void Player::clearHand(){
}

// 获得 玩家每轮投注到桌面的筹码
int Player::getTempScore(){
	return tempScore;
}

// 设置 玩家每轮投注到桌面的筹码
void Player::addTempScore(int _tempScore){
    this->subRoomScore(_tempScore);
	this->tempScore += _tempScore;
}

void Player::subTempScore(int _tempScore){
    this->tempScore -= _tempScore;
}


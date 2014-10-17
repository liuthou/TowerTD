//
//  Player.h
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-13.
//
//  姓名   时间         修改内容
//  袁文龙 2014年9月18日 修改玩家属性
//
//	 继尚 2014年9月19日 修改 bool GameState=0;
//
//
//

#ifndef __TexasPoker__Player__
#define __TexasPoker__Player__

#include <iostream>
#include <cocos2d.h>
using namespace cocos2d;

#include "Poker.h"

namespace TexasPoker {
    class PokerAction;
	class Function;
	class PokerArray;

    /**玩家游戏状态*/
    enum class ePlayerGameState{
        /**正常*/
        NORMAL = 1 ,
		/**站起*/
		STANDUP,
        /**弃牌*/
        FOLD
    };
    
    enum class ePlayerType{
        /**普通玩家*/
        NORMAL,
        /**电脑玩家*/
        AI
    };
    
    /**玩家*/
    class Player : public Node{
	public:
		/**玩家个人固有(非游戏中)属性*/
		CC_SYNTHESIZE(int, id, ID);	///< 玩家id

		CC_SYNTHESIZE(std::string, name, Name);		///< 玩家姓名

		CC_SYNTHESIZE(char, sex, Sex);		///< 玩家性别	

		CC_SYNTHESIZE(int, totalScore, TotalScore);		///< 玩家总积分
        
        /**
         *  玩家房间的内的筹码
         */
		CC_SYNTHESIZE(int, score, Score);			///< 玩家房间的内的筹码

		CC_SYNTHESIZE(std::string, playerImageFileName, PlayerImageFileName);			///< 玩家头像文件名

    public:
		/**玩家个人游戏中属性*/
		CC_SYNTHESIZE(ePlayerType, playerType, PlayerType);	///< 玩家类型:普通玩家,AI电脑

		CC_SYNTHESIZE(int, playerIndex, PlayerIndex);	///< 玩家的当前位置

		CC_SYNTHESIZE(ePlayerGameState,playerGameState,PlayerGameState);	///< 玩家游戏状态

		CC_SYNTHESIZE(bool,gameState,GameState);	///< 是否正在进行游戏中 true Or false

		CC_SYNTHESIZE(PokerAction *, poker_Action, Poker_Action);	///< 动作管理器


		CC_SYNTHESIZE(PokerArray *, poker_Array, Poker_Array);	///< 玩家的 手牌和河牌

	public:
        /**Player 的 init() */
		virtual bool init(ePlayerGameState playerGameState, int _id,
			std::string name, char sex, int totalScore, int score);

		/**增加玩家的房间内携带积分*/
		void plusRoomScore(int _score);

		
		/**玩家清除手牌*/
		void clearHand();

		/**获得 玩家每轮投注到桌面的筹码*/
		int getTempScore();
        
		/**设置 玩家每轮投注到桌面的筹码*/
		void addTempScore(int _tempScore);
        
        /**
         *  减少玩家的每轮投注到桌面的临时筹码,分池时需要使用此函数
         *
         *  @param _tempScore 要减少的筹码
         */
        void subTempScore(int _tempScore);
    private:
        int tempScore;		///< 玩家每轮投注到桌面的筹码

        /**减去玩家的房间内携带积分*/
		void subRoomScore(int _score);
    };
}
#endif /* defined(__TexasPoker__Player__) */

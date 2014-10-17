//
//  ProcessControl.h
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-13.
//
//

#ifndef __TexasPoker__ProcessControl__
#define __TexasPoker__ProcessControl__

#include <iostream>
#include <cocos2d.h>
using namespace cocos2d;

#include "Player.h"
#include "Poker.h"
#include "ChipPool.h"
#include "ChipPoolControl.h"

namespace TexasPoker {
    class Room;
    class PokerAction;
    
    /**流程控制器*/
    class ProcessControl : public Node{
    public:
        /**流程状态*/
        enum class ProcessState{
            Null,
            
            /**游戏开始,发手牌*/
            Start,
            
            /**第一轮. 小,大盲注,下注循环*/
            Perflop,
            PerflopLittleBlind,
            PerflopBigBlind,
            PerflopLoopPokerAction,
            /**第一轮结束,翻三张牌*/
            PerflopEnd,
            
            /**第二轮*/
            Flop,
            FlopLittleBlindCheck,
            FlopLoopPokerAction,
            /**第二轮结束,翻第四张牌*/
            FlopEnd,
            
            /**第三轮*/
            Turn,
            TurnLittleBlindCheck,
            TurnLoopPokerAction,
            /**第三轮结束,翻第五张牌*/
            TurnEnd,
            
            /**第四轮*/
            River,
            RiverLittleBlindCheck,
            RiverLoopPokerAction,
            /**最后一轮下注结束*/
            RiverEnd,
            /**
             1. 结算
             2. 清台,分数<5的玩家需要获取玩家属性的筹码,加入到台面筹码
             如果玩家属性内没有筹码,从椅子上站起
             3. 把所有玩家的游戏状态设置为false
             player->GameState = false;
             4. 通知Room重新开始一个新的流程*/
            Clear
        };
        
    public:
        static ProcessControl* create(Room *room);
        
        /**索引*/
        void Index();
        
        /**游戏开始:
         1. 设置玩家状态为正在游戏中
         player->GameState = true;
         1. 分配庄家
         2. 发手牌
         */
        void Start();
        
        
        
        
        /**发手牌
         开始给玩家发手牌
         发牌动画执行结束,回调 Index();
         */
        void    DealingPokers();
        int     DealingPokersAnimationIndex;
        int     DealingPokersAnimationLoopNumber;
        void    DealingPokersAnimation();
        
        /**盲注:
         +++++++++++++++++++++++++++++第一轮++++++++++++++++++++++++++++++++
         1. 设置当前状态
         2. 回调Index();
         */
        void Perflop();
        /**
         1. 设置当前状态
         2. 小盲注下注动画，每一局的第一轮，小 大盲注没有发牌的时候就会自动下注，即我们需
         3. 动画结束回调Index();
         auto pokerAction = PokerAction::createLittleBlinds(this);
         */
        void PerflopLittleBlind();
        void PerflopBigBlind();
        void PerflopLoopPokerAction();
        void PerflopEnd();
        
        
        
        /**翻盘三张
         +++++++++++++++++++++++++++++第二轮++++++++++++++++++++++++++++++++:
         1. 小盲注叫牌:弃牌,看牌,下注
         littleBlindsPlayer->PokerAction->LittleBlinds();
         2. loopPokerAction
         auto betingPlayer = NextPlayer(littleBlindsPlayer)
         create(betingPlayer);
         */
        void Flop();
        void FlopLittleBlindCheck();
        void FlopLoopPokerAction();
        /**第二轮结束,翻第四张牌*/
        void FlopEnd();
        
        
        
        
        /**翻第四章
         +++++++++++++++++++++++++++++第三轮++++++++++++++++++++++++++++++++:
         1. 小盲注叫牌:弃牌,看牌,下注
         littleBlindsPlayer->PokerAction->LittleBlinds();
         2. loopPokerAction
         auto betingPlayer = NextPlayer(littleBlindsPlayer)
         create(betingPlayer);
         */
        void Turn();
        void TurnLittleBlindCheck();
        void TurnLoopPokerAction();
        /**第三轮结束,翻第五张牌*/
        void TurnEnd();
        
        
        
        
        /**发第五张牌
         +++++++++++++++++++++++++++++第四轮++++++++++++++++++++++++++++++++:
         1. 小盲注叫牌:弃牌,看牌,下注
         littleBlindsPlayer->PokerAction->LittleBlinds();
         2. loopPokerAction
         auto nextPlayer = NextPlayer(littleBlindsPlayer)
         create(nextPlayer);
         */
        void River();
        void RiverLittleBlindCheck();
        void RiverLoopPokerAction();
        /**最后一轮下注结束*/
        void RiverEnd();
        
        
        
        
        /**亮牌结算
         1. 亮牌
         2. 结算
         3. 再给下一局设置庄家
         */
        void Clear();
        
        
        /**
         *  延时调用Index
         */
        void delayTimeIndex(float time);
        
        /**
         *  翻河牌
         */
        void turnRiverPoker();
        /**
         *  在河牌里添加一张扑克
         */
        void addRiverPoker();
        
    public:
        /**创建流程控制,  不能使用，原因是 static*/
        virtual bool init(Room *room);
        
        /**
         *  设置玩家(Player)的tempScore和ProcessControl的lastBetScore(最后一次下注)
         *
         *  @param player    玩家指针
         *  @param tempScore 下注金额
         */
        void addPlayerTempScore(Player *player,int tempScore);
        
        
        Room * getRoom();
        
        /**根据一个玩家的 playerIndex,  返回他的下家*/
        Player * NextPlayer(int playerIndex);
        
        /**
         *  返回他的上一个玩家是谁,一般用此函数作为判断此轮结束玩家
         *
         *  @param currentPlayer 当前玩家
         *
         *  @return 返回当前玩家的上一个玩家
         */
        Player * PrePlayer(int playerIndex);
        
        /**
         *  设置庄家
         *  @param chairNumber 传入一个当前椅子号
         *  @return 返回true已经设置成,false没有设置成功
         */
        void SetDealerPlayer(int chairNumber);
        
        /**
         *  遍历所有玩家,统计玩家当前牌型,并且存入player的poker_array内
         */
        void SetPlayerPokerMethod();
        
        /**最后一次下注金额*/
        CC_SYNTHESIZE(int,lastBetScore,LastBetScore);
        
        /**当前下注玩家*/
        CC_SYNTHESIZE(Player *, BetingPlayer, BetingPlayer);
        
        /**小盲注,玩家指针*/
        CC_SYNTHESIZE(Player *, littleBlindsPlayer, LittleBlindsPlayer);
        
    protected:
        
        /**庄家,玩家指针 (NULL)*/
        Player * DealerPlayer;
        
        /**大盲注,玩家指针*/
        Player * BigBlindsPlayer;
        
        /**庄家的椅子编号 (0)*/
        int DealerPlayerChair;
        
        /**房间(用来拿到房间中的庄家椅子号)*/
        Room * room;
        
        /**筹码底池*/
        ChipPoolControl * chipPoolControl;
        
        /**在控制流程中的椅子数组*/
        Map<int, Player *> ChairsAtProcess;
        
        /**一副洗好的扑克牌 */
        Vector<Poker *> wholePokers;
        
        /**
         *  河牌
         */
        Vector<Poker *> riverPokers;
    public:
        
        /**当前流程状态 (ProcessState::Null)*/
        CC_SYNTHESIZE(ProcessState,nowProcessState,NowProcessState);
    private:
        /**创建一副洗好的牌*/
        void newWholePokers();
        
        /**
         *  刷新玩家tempScore的Label
         */
        void flushPlayerTempScoreAndPlayerItemLabel();
        void flushPlayerTempScore(Player * player, MenuItemSprite *playerItem);
        void flushPlayerTopLabel(Player * player, MenuItemSprite *playerItem);
        
        /**
         *  当前河牌的个数
         */
        int nowRiverPokerNumber;
        
    };
}
#endif /* defined(__TexasPoker__ProcessControl__) */

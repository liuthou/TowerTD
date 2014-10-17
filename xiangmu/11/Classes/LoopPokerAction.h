//
//  LoopPokerAction.h
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-13.
//
//

#ifndef __TexasPoker__LoopPokerAction__
#define __TexasPoker__LoopPokerAction__

#include <iostream>
#include <cocos2d.h>
using namespace cocos2d;

#include "Player.h"

namespace TexasPoker {
    
    class ProcessControl;
	class PokerAction;
	class AiPlayerAction;
    
    /**流程内的循环调度
     弃牌,跟注,加注
     
     1. 无加注流程
     beginPlayer下注时 AND 最后一次加注玩家指针为空
     通过玩家 MAP 获取 beginPlayer 的 iterator,之后 iterator-- 获得此轮结束玩家
     .....
     
     2. 有加注流程
     当有人加注,设置加注者的lastRaisePlayer指针
     然后得出 lastPlayer
     
     注意点:
     每一次玩家下注都要判断结束玩家, 有人会中途站起
     if( beginPlayer && lastRaisePlayer==NULL){
     lastPlayer = processControl.PrePlayer(beginPlayer);
     }else if (lastRaisePlayer){
     lastPlayer = processControl.PrePlayer(lastRaisePlayer);
     }
     
     当lastPlayer的指针 == 当前下注玩家的指针
     下注完毕之后,循环结束,根据当前轮数来判断执行哪个轮的End
     例如是第一轮就执行PerflopEnd;
     
     
     需要判断得出:
     流程结束的玩家
     Player * lastPlayer;
     2. 如果有人加注,记录下加注玩家指针,并且计算
     */
    class LoopPokerAction: public Node{
    public:
		/**获得循环流程开始 下注的玩家指针*/
		static LoopPokerAction * create(ProcessControl * processControl);
        
        /**
         流程开始:
         1. 判断此玩家是否是当前流程的最后一个玩家
         2. 如果不是最后一个玩家,执行
         pokerAction =  PokerAction::reate(this);
         pokerAction->Bet();
         */
        void BetEnd();
        
        /**
         初始化流程配置:
         1.预加载资源
         2.设置流程结束玩家
         */
        virtual bool init(Player *betingPlayer);
    public:
        /**玩家指针*/
        
        /**设置最后一次加注玩家*/
        void setLastRaisePlayer();
        
        /**设置流程结束的玩家*/
        //void setLastPlayer();
        
	public:
        
        /**当前下注玩家*/
        Player * betingPlayer;
		
        
        /**流程开始时的玩家
         1. 此变量只赋值一次,仅在创建此loop时赋值
         */
        Player * beginPlayer;
        
        /**流程结束的玩家*/
        Player * lastPlayer;
        
        /**最后一次加注玩家*/
        Player * lastRaisePlayer;
        
        ProcessControl * processControl;
        
		/**玩家操作 Layer 的按钮, 也即 PokerAction*/
		PokerAction *pokerAction;
        
		/**玩家操作 Layer 的按钮, 也即 PokerAction*/
		AiPlayerAction *aiAction;
		
		/**结束 玩家的 loopAction*/
		std::function<void ()> endFunc;
        
    };
}
#endif /* defined(__TexasPoker__LoopPokerAction__) */

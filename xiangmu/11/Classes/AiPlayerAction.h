//
//  AiPlayerAction.h
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-13.
//
//

#ifndef __TexasPoker__AiPlayerAction__
#define __TexasPoker__AiPlayerAction__

#include <iostream>
#include "ProcessControl.h"
#include "PokerAction.h"
#include "Player.h"
#include "Room.h"
#include "Function.h"


namespace TexasPoker {
	/**
		*AiPlayerAction虽然继承于PokerAction,但是它除了第一轮的大小盲注跟PokerAction一样，其他的都是由它
			本身的AI算法决定
	*/
    class AiPokerAction : public PokerAction {
	public:

		static AiPokerAction* create(ProcessControl * processControl);
        
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
        virtual void Bet();

		/**看牌; 弃牌,看牌,下注
         1. 加入时间调度器，进度条动画
            1.1 看牌
                this->Pass();
            1.2 下注
                this->Call();
            1.3 弃牌
                this->Fold();
         */
        virtual void Check();
		
	private:
        
		/**回调加注*/
		virtual void onRaise();
        
        virtual bool init();
        

        
    };
        
};
#endif /* defined(__TexasPoker__AiPlayerAction__) */

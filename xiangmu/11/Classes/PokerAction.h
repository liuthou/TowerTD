//
//  PokerAction.h
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-13.
//
//

#ifndef __TexasPoker__PokerAction__
#define __TexasPoker__PokerAction__

#include <iostream>
#include "cocos2d.h"
#include "Player.h"
#include "Room.h"

#include "BetTimePokerAnimation.h"

using namespace cocos2d;


namespace TexasPoker {
    class LoopPokerAction;
    class ProcessControl;
    
    /**叫注/说话 - 一个玩家的决定*/
    class PokerAction : public Layer{
	protected:
        /**
         *  当前类的语言包
         */
        ValueMap languagePokerAction;
        
        /**
         *  playerItem头部的Label
         */
        Label * topLabel;
        
        /**
         *  Room内的玩家playerItem
         */
        MenuItemSprite * playerItem;
        
        /**当前下注玩家*/
        Player *betingPlayer;
        
        /**获得最多可携带最高金额*/
        int RoomScoreMax;
        
        /**获得最低下注金额*/
        int RoomScoreMin;    
        
    public:
        
        enum class ActionType{
            /**小盲注*/
            LittleBlinds = 0,
            /**大盲注*/
            BigBlinds,
            /**押注*/
            Bet,
            /**看牌*/
            Check
        };
        
        static PokerAction* create(ProcessControl * processControl);
                
        /**押注bet(); 弃牌,跟注,加注
         1. 弹出菜单
         2. 设置时间调度器: betTime ,时间结束之后回调: 弃牌

         为一个玩家创建一个下注动作
         player = loopPokerAction->getBetingPlayer();
         
         三个按钮触发功能:
         1. 弃牌按钮
            this->Fold();
         2. 跟注按钮
            this->Call();
         3. 加注按钮
            this->Raise();
        */
        virtual void Bet();
        
        
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
        virtual void Check();
        
        
        /**小盲注
            1. 直接抛出,最低筹码
            2. 小盲注结束
         */
        virtual bool LittleBlinds();

        /**大盲注
         直接抛出 最低筹码*2
         */
        virtual bool BigBlinds();

		/**抛筹码动画,根据筹码调用相应方法*/
		/*void throwChips(int chip);
		void throw_5_Chips();
		void throw_10_Chips();
		void throw_20_Chips();*/
        
	public:
		/**通过回调至processControl索引Index（）*/
//		std::function<void()> _blindsEnd;

		/**保存触发后状态*/
		std::function<void()> endFunc;

		/**设置 loopPokerAction 中的加注玩家 */
		std::function<void()> raisePlayer;
        
	public:
        /**
         *  延时运行一个无参的函数
         *
         *  @param std::function<void 无参函数 CC_CALLBAKC_0来绑定
         */
        void delayRun(std::function<void()> func);
        
        BetTimePokerAnimation * betTimePokerAnimation;
        
		/**
		 *  保存流程控制器的指针,可以获得room的椅子
		 */
		ProcessControl * processControl;
        
		/**
		 *  初始化
		 */
		virtual bool init();
        /**
         初始化成员变量
         */
        virtual void initData();
        
        /**动作完毕
            当前动作全部结束,重新调用loopPokerAction的bet;
			即，点击某个按钮后，触发相应的事件，并返回动作结束
            loopPokerAction->bet();
         */
        virtual void End();
        
        /**
         *  结束并且运行一次筹码的移动动画
         */
        void EndAndRunBetMoverAnimation();
        
        /**
         *  增加一个时间滚动条动画
         */
        virtual void addTimer();
        
        
        /**弃牌
         1. 给玩家设置弃牌状态
         2. 跳过此人
         3. this->End();
         */
        virtual void Fold();

		/**回调弃牌*/
		void onFold(Ref* pSender);

        /**跟注*/
        virtual void Call();

		/**回调跟注*/
		void onCall(Ref* pSender);
        
        /**加注
         (1). 加注金额不能大于场内任何一人的最大携带金额
         (2). 每轮每人只能加注最多两次,如果超过2次自动跳过
         (3). 加注金额为自身所有携带积分,提示ALLIN
         
         player = loopPokerAction->getBetingPlayer();
         loopPokerAction->setLastRaisePlayer(player);
         this->End();
         */
		/**加注*/
        virtual void Raise(int chip);

		/**回调加注*/
		virtual void onRaise(Ref* pSender);
        
        /**跳过; 看牌*/
        virtual void Pass();

		/**回调看牌*/
		virtual void onPass(Ref* pSender);

		/**ALLINT*/
		virtual void AllIN();
    };
}
#endif /* defined(__TexasPoker__PokerAction__) */

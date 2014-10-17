//
//  Poker.h
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-13.
//
//

#ifndef __TexasPoker__Poker__
#define __TexasPoker__Poker__

#include <iostream>
#include <cocos2d.h>
using namespace cocos2d;

#include "Global.h"

namespace TexasPoker {
    /**标准化枚举: 所有玩法的牌型*/
    enum class PokerMethod{
        /**皇家同花顺 同花顺 + 最高连号以A为最高牌的牌型 A,K,Q,J,10*/
        RoyalFlush,
        
        /**同花顺 ,同花 + 顺子*/
        StraightFlush,
        
        /**四条 , 4个数字一样 */
        FourOfAKind,
        
        /**葫芦, 三条 + 一对*/
        Fullhouse,
        
        /**同花, 5张牌同色*/
        Flush,
        
        /**顺子 , 5张连号牌*/
        Straight,
        
        /**三条 , 3个牌数字一样*/
        ThreeOfAKind,
        
        /**两对*/
        TwoPairs,
        
        /**一对*/
        OnePair,
        
        /**高牌*/
        HighCard

	
    };
    
    /**标准化类: 每个扑克牌的花色*/
    enum class pokerColor{
		/**黑桃*/
		SPADE = 1,
        /**红桃*/
        HEART = 2 ,
		/**梅花*/
		CLUB = 3,
        /**方块*/
        DIAMOND = 4
    };
    
    /**标准化类: 每个扑克牌的*/
    class Poker : public Sprite{
    public:
        /**牌的数字
         2 - 14
         11:J
         12:Q
         13:K
         14:A
         */
	
        CC_SYNTHESIZE(int, number, No);

        /**牌的花色*/
		CC_SYNTHESIZE(pokerColor, color, PokerColor);
	public:
		/**
		 *  C++的构造函数不要使用,使用coocs2d的构造函数
         *  使用工厂方法的autorelease();
		 */
		static Poker * create(pokerColor color, int number);
		bool init(pokerColor color, int number);
    };
    
    /**标准化类: 扑克牌数组,玩家2张,河牌5张;如果没有则要设置为NULL*/
    class PokerArray : public Ref{
		protected:
			/**玩家手牌:hand1,hand2*/
			Vector<Poker *> handVector;

			/**河牌:river1 - river5*/
			Vector<Poker *> riverVector;		
            
			void PokerSort();

		public:
        void setRiverVector(Vector<Poker *> river);
			/**PokerArray 的 创建*/
			static PokerArray* create();

			/**PokerArray 的 init()*/
			bool init();

			/**玩家获得手牌:hand1,hand2*/
			void setHandVector(Poker * poker);

			/**返回玩家手牌:hand1,hand2*/
			Vector<Poker *> getHandVector();

			/**玩家的牌型*/
			CC_SYNTHESIZE(TexasPoker::PokerMethod, poker_Method, Poker_Method);

		public:
			/**玩家的最好牌*/
			Vector<Poker *>  bestPokerGroup;
			/**手牌加河牌数组*/
			Vector<Poker* > allPokerVector;
    };
}
#endif /* defined(__TexasPoker__Poker__) */

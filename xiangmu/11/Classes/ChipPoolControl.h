//
//  ChipPoolControl.h
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-25.
//

#ifndef __TexasPoker__ChipPoolControl__
#define __TexasPoker__ChipPoolControl__

#include <iostream>
#include <cocos2d.h>
using namespace cocos2d;


#include "Player.h"
#include "ChipPool.h"

namespace TexasPoker{
    class ChipPoolControl: public Layer{
        public:
        virtual bool init();
        CREATE_FUNC(ChipPoolControl);
            
        void pushBegin();
        void pushScore(Player * player);
        void pushEnd();
        
        /**返回积分池*/
        Vector<ChipPool * > getChipPoolVector();
        
        private:
        
        /**
         *  积分池
         */
        Vector<ChipPool * > chipPool;
        
        /**
         *  临时变量
         */
        Vector<Player *> tempPlayer;
        
        /**
         *  向最后一个ChipPool里塞数据
         *
         *  @param player 玩家指针
         *  @param Score  添加的积分
         */
            void addPlayerToChipPool(Player * player,int Score);
        
        /**
         *  在一个数组内查找一个积分是否存在于此玩家
         *
         *  @param score      一个 int 积分
         *  @param tempPlayer 玩家数组
         *
         *  @return 返回一个等于此积分的玩家指针
         */
            Player * findPlayerScoreForVector(int score,Vector<Player *> tempPlayer);
        
        Menu * _menu;
        
        int MenuItemNumber;
        
        void createChipPool();
        void freshChipPoolItemLabel();
    };
    
};
#endif /* defined(__TexasPoker__ChipPoolControl__) */

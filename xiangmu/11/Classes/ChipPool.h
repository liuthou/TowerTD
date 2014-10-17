//
//  ChipPool.h
//  TexasPoker
//
//  Created by Ô¬ÎÄÁú on 14-9-16.
//
//

#ifndef __TexasPoker__ChipPool__
#define __TexasPoker__ChipPool__

#include <iostream>
#include <cocos2d.h>
using namespace cocos2d;

#include "Player.h"

namespace TexasPoker{
    
    class ChipPool : public Node {
    public:
        int totalScore;
        Vector<Player *> players;
        
        void add(Player *player,int Score);
        
        virtual bool init();
        CREATE_FUNC(ChipPool);
    };
}
#endif /* defined(__TexasPoker__ChipPool__) */

//
//  ChipPool.cpp
//  TexasPoker
//
//  Created by Ô¬ÎÄÁú on 14-9-16.
//
//

#include "ChipPool.h"

#include "Global.h"

using namespace TexasPoker;

bool ChipPool::init(){
    
    totalScore = 0;
    
    return true;
}

void ChipPool::add(Player *player,int Score){
    auto it = players.find(player);
    if (it == players.end()) {
        players.pushBack(player);
    }
    
    totalScore +=Score;
}
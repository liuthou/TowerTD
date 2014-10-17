//
//  DealingPokersAnimation.h
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-29.
//
//  发牌
//

#ifndef __TexasPoker__DealingPokersAnimation__
#define __TexasPoker__DealingPokersAnimation__

#include <iostream>
#include <cocos2d.h>
USING_NS_CC;

#include "PokerAnimation.h"
#include "Player.h"

class DealingPokersAnimation :public PokerAnimation{
public:
    void dealing(int index);
    void dealingEnd();
    static DealingPokersAnimation* create(ProcessControl *processControl);

private:
    virtual bool init(ProcessControl *processControl);

    Vec2 startPoint;
    
    MenuItemSprite * playerItem;
    Player * player;
    
    Sprite * dealSprite;
    Animate * fapaiAnimate;
    MoveTo * dealMoveTo;
    
    void initUI();
};

#endif /* defined(__TexasPoker__DealingPokersAnimation__) */

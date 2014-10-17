//
//  BetTimePokerAnimation.h
//  TexasPoker
//
//  Created by CJs on 14-9-29.
//
//  下注时间
//

#ifndef __TexasPoker__BetTimePokerAnimation__
#define __TexasPoker__BetTimePokerAnimation__

#include <iostream>
#include <cocos2d.h>
USING_NS_CC;

#include "PokerAnimation.h"
#include "Player.h"

class BetTimePokerAnimation :public PokerAnimation{
public:
	void bettingTime(int index);
	void bettingTimeEnd();
	static BetTimePokerAnimation* create(ProcessControl *processControl);
    
    ProgressTimer * getTimer(){
        return timer;
    };
private:
	virtual bool init(ProcessControl *processControl);

	Vec2 startPoint;

	MenuItemSprite * playerItem;
	Player * player;


	/**进度条计时器*/
	ProgressTimer * timer;
	/**进度条的形状 精灵*/
	Sprite * spShape;
	/**进度条 进度范围*/
	ProgressFromTo * doingProgress;
	
	virtual void initUI();
};

#endif /* defined(__TexasPoker__BetTimePokerAnimation__) */

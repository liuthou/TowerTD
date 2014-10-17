//
//  ScoreLayer.h
//  heroJump
//
//  Created by lius on 14-9-17.
//
//

#ifndef __heroJump__ScoreLayer__
#define __heroJump__ScoreLayer__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class ScoreLayer:public Layer {
private:
	Label * curScoreLabel;
	Label * curCoinLabel;
	Label * curMetersLabel;
	int curScore;
	int maxScore;
	int curCoin;
	int maxCoin;
	int curMeters;
	int maxMeters;
	Size vSize;
public:
	int getCurScore();
	int getCurCoin();
	int getCurMeter();
	void recvAward(Ref * obj);
	void onEnter();
	void addLabel();
    virtual bool init();
    CREATE_FUNC(ScoreLayer);
};
#endif /* defined(__heroJump__ScoreLayer__) */

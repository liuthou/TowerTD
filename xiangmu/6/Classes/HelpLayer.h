//
//  HelpLayer.h
//  heroJump
//
//  Created by liuly on 14-9-19.
//
//

#ifndef __heroJump__HelpLayer__
#define __heroJump__HelpLayer__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class HelpLayer:public Layer {


public:
	virtual bool init(int dateType);
	static HelpLayer * create(int dateType);
	void useHelp(int dateType);
private:
	//Animation function board
	void boardAnimation();
	//The animation of the monkey holster
	void holsterAnimation();
	void update(float t);
	Size visize;
	Sprite *board;
	Sprite * finger;
	Size b_size;

};
#endif /* defined(__heroJump__ScoreLayer__) */

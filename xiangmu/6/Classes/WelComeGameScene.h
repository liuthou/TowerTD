//
//  WelComeGameScene.h
//  heroJump
//
//  Created by mazhai on 14-9-16.
//
//

#ifndef __heroJump__WelComeGameScene__
#define __heroJump__WelComeGameScene__

#include <iostream>
#include "cocos2d.h"

/**
 *  load data and show Animation
 */
USING_NS_CC;
class WelComeGameScene : public Layer{

protected:

	//the Sprite change member variable
	Sprite * bg;
	//the scrn size
	Size vSize;

protected:

	// add label in the layer
	void addLabel();
	//call function
	void onEnter();
    
public:
    
    
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(WelComeGameScene);
protected:
};

#endif /* defined(__heroJump__WelComeGameScene__) */

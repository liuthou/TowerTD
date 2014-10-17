#ifndef __GAMEOVERLAYER_H_
#define __GAMEOVERLAYER_H_

#include "cocos2d.h"
using namespace cocos2d;

class GameOverLayer:public Layer {
public:
	virtual bool init();
	CREATE_FUNC(GameOverLayer);

	//static Scene *createScene();
protected:
	Size vSize;
	virtual void onEnter();
	void addTouch();
	Label* addScore();
};

#endif
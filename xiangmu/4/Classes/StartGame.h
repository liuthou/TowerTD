#ifndef _STARTGAME_H
#define _STARTGAME_H
#include "cocos2d.h"
USING_NS_CC;
class StartGame : public Layer{
public:
	virtual void onEnter();
	static Scene * createScene();
	CREATE_FUNC(StartGame);
	virtual bool init();
};
#endif // !_STARTGAME_H

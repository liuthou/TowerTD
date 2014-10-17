/*
*主场景层
*/

#ifndef __GAMELAYER__
#define __GAMELAYER__

#include "cocos2d.h"
/************************************************************************/
/* 游戏层                                                                     */
/************************************************************************/
class GameLayer : public cocos2d::Layer
{
private:
	//开始游戏
	void startGame();
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameLayer);
};

#endif // __HELLOWORLD_SCENE_H__

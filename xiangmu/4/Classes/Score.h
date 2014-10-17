#ifndef __HEROESLAYER__
#define __HEROESLAYER__

#include "cocos2d.h"
/************************************************************************/
/* 积分层 放置积分以及暂停按钮                                                                     */
/************************************************************************/
class HeroesLayer : public cocos2d::Layer
{
protected:
	//拿到积分
	void getScore();
	//积分显示
	void viewScore();
	//创建暂停按钮
	void createPause();
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(HeroesLayer);
};

#endif // __HELLOWORLD_SCENE_H__
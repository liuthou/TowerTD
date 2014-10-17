#ifndef __GAMESCENE_H_
#define __GAMESCENE_H_
#include "cocos2d.h"
USING_NS_CC;

class GameScene : public Scene{
public:
	CREATE_FUNC(GameScene);
	//得到背景层
	Layer * getBackgroundLayer();
	//得到控制层
	Layer * getControlLayer();
	//得到主角层
	Layer * getRoleLayer();
protected:
	virtual bool init();
	void onEnter();
	int audioFlag;
};

#endif // !__GAMESCENE_H_

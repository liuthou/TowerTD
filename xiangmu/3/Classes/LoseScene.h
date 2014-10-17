#ifndef __LOSESCENE_H_
#define __LOSESCENE_H_
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class LoseScene:public Layer{
public:
	CREATE_FUNC(LoseScene);
	virtual bool init();
	static Scene* createScene();
	virtual void onEnter();
protected:
	Scale9Sprite* flashsprite;
	void clearCaches();
	Sprite* bg;
	void showBg();
	//Ë«»÷
	void changeClick(float dt);
	bool doubleclick;
};
#endif
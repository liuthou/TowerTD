#ifndef __LEVELLAYER_H
#define __LEVELLAYER_H
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;
using namespace cocostudio;



class LevelLayer : public Layer
{
private:

	Vec2 layerPos;
	int layerNum;	
	int levelPages;
	float WINDOW_WIDTH;
	float WINDOW_HEIGHT;
public:
	LevelLayer();
	~LevelLayer();

	virtual bool init();
	static Scene* createScene();
	CREATE_FUNC(LevelLayer);
private:
	//移动当前菜单
	void moveLeft();
	void moveRight();
protected:
	//介绍塔的信息
	void introduceTower();
	//帮助信息
	void help();
	//这三个状态分别的设定层的限制 是否重复贴层
	CC_SYNTHESIZE(bool,isVisble1,IsVisble1);
	CC_SYNTHESIZE(bool,isVisble2,IsVisble2);
	CC_SYNTHESIZE(bool,isVisble3,IsVisble3);
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
	//关于信息
	void About();
	Menu *menu3;
	Menu *menu4;
	Layer * layer;
};


#endif /* defined(__thiefTD__LevelLayer__) */
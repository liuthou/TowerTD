#ifndef __MAINSCENE_H_
#define __MAINSCENE_H_
#include "MapLayer.h"
#include "GameLayer.h"
#include "cocos2d.h"
USING_NS_CC;
class MonsterManager;
class ForwardLayer;
class InjuredEffect;
class TouchLayer;
class GameLayer;
class MapLayer;
class BackgroundLayer;
class GameLayer;
class FileManager;
class BasicAttribute;
class MonsterAttribute;
class MonsterManagerAttribute;
class TowerAttribute;
class MainScene:public Scene{
public:
	static Scene* create(std::string filename,int chapternum);
	virtual bool init(std::string filename,int chapternum);
	MapLayer *getMapLayer();
	Layer * getGameLayer();
	//初始化游戏,异步加载资源
	void initGame();
	//成功界面
	void win();
	//失败界面
	void lose();
	CC_SYNTHESIZE(std::string,filename,FileName);
	//当前运行关卡
	CC_SYNTHESIZE(int,chapternum,Chapternum);
private:
	void changeWinScene();
	void changeLoseScene();
	void initLayers();
	MonsterManager* monstermanager;
	ForwardLayer* forwardlayer;
	InjuredEffect* injuredlayer;
	TouchLayer* touchlayer;
	GameLayer* gamelayer;
	MapLayer* maplayer;
	BackgroundLayer* backgroundlayer;
	GameLayer* gameLayer;
	FileManager* filemanager;
	~MainScene();
};
#endif
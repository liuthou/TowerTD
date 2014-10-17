//游戏场景控制器,负责创建与切换场景
#ifndef __SCENEMANAGER_H_
#define __SCENEMANAGER_H_
#include "cocos2d.h"
USING_NS_CC;
class SceneManager:public Node{
public:
	static SceneManager* getInstance();
private:
	SceneManager();
	virtual ~SceneManager();
	SceneManager(const SceneManager &scenemanager);
	SceneManager* operator=(const SceneManager &scenemanager);
private:
	static SceneManager* scenemanager;
};
#endif
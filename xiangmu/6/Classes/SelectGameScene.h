//
//
//SelectGameScene.cpp
//
//
//create by lius  9ÔÂ29ÈÕ
//
#ifndef __SELECTGAMESCENE_H_
#define __SELECTGAMESCENE_H_
#include "cocos2d.h"
using namespace cocos2d;
class SelectGameScene:public Layer{
protected:
	Size vSize;
	Label * curScoreLabel;
	Label * maxScoreLabel;
	Label * maxMetersLabel;
public:

	void addButton();

	void onEnter();

	void TestUserDefaule();

	virtual bool init();

	CREATE_FUNC(SelectGameScene);

	static Scene * creatScene();

	void addLabel();

	void addScore();

};
#endif
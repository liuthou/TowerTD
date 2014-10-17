#ifndef __LOADINGLAYER_H
#define __LOADINGLAYER_H
#include "cocos2d.h"
using namespace cocos2d;
class LoadingLayer:public Layer{
	
	int resCount; //res count
	int resSum; // all res count
	void addSprite();
	void update(float t);
	~LoadingLayer();
public:
	virtual bool init();
	CREATE_FUNC(LoadingLayer);
	static Scene *createScene();
};
#endif
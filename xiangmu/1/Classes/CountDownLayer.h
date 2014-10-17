#pragma once;
#include "cocos2d.h"
using namespace cocos2d;
class  CountDownLayer:public Layer
{
public:
	virtual bool init();
	static Scene * createScene();
	CREATE_FUNC(CountDownLayer);
    
protected:
    
    virtual void registerNoTouch();
    
private:
	int i = 0;
	Sprite * countDownSprite;
	void Num1(float t);
	void Num2(float t);
	void Num3(float t);
	void GameGo(float t);
	void Circle();
	void runArrow1(float t);
	void runArrow2(float t);
	void runArrow3(float t);
	void clearArrow(float t);
	void childDispear(float t);
};
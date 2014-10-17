//
//TokenRect.cpp
//
//
//create by lius 9ÔÂ24ÈÕ
//
//
#ifndef __TOKENQQ_H_
#define __TOKENQQ_H_
#include "cocos2d.h"
#include "BaseRewards.h"
using namespace cocos2d;
class TokenRect:public BaseRewards{
public:
	void onEnter();
	void addCoinAnimation();
	virtual bool init(std::string fileName);
	static TokenRect * create(std::string fileName);
};
#endif
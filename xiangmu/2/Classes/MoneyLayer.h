#ifndef __MONEYLAYER_H
#define __MONEYLAYER_H
#include "cocos2d.h"

using namespace cocos2d;

class MoneyLayer :public Layer
{
private:
	Layer * moneybg;
public:
	virtual bool init();
	CREATE_FUNC(MoneyLayer);
	static Scene * createScene();
	void money(Ref * sender);
	void update(float t);
};

#endif
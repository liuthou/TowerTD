#ifndef __STORESELECTLAYER_H_
#define __STORESELECTLAYER_H_
#include "cocos2d.h"
using namespace cocos2d;
class StoreSelectLayer:public Layer
{
public:
	virtual bool init(int money);
	static StoreSelectLayer * create(int money);
	//CREATE_FUNC(StoreSelectLayer);
protected:
	int willReduceMoney;
	void sendInform(Ref * sender);
	void removeSelfLayer(Ref * sender);
	void addShiledLayer();
private:
};
#endif
#ifndef __BASEGOLDCOIN_H_
#define __BASEGOLDCOIN_H_
#include "cocos2d.h"
#include "BaseRewards.h"
using namespace cocos2d;
class BaseGoleCoin:public BaseRewards{
public:
	virtual bool init(std::string fileName,int id_x,int id_y);
	static BaseGoleCoin * create(std::string fileName,int id_x,int id_y);
	CC_SYNTHESIZE(bool,isdie,Isdie);
	virtual void onEnter();
	virtual void addAnimation();
    virtual void collisionRole();
};
#endif
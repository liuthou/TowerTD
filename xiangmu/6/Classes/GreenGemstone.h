#ifndef __GREENGEMSTONE_H_
#define __GREENGEMSTONE_H_
#include "cocos2d.h"
#include "BaseGemstone.h"
using namespace cocos2d;
class GreenGemstone:public BaseGemstone{
protected:
	int score;
	int coin;
public:
	virtual bool init(std::string fileName,int r_id_x,int r_id_y);
	static GreenGemstone * create(std::string fileName,int r_id_x,int r_id_y);
    virtual std::string sendCast();
};
#endif
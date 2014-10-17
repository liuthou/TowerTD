#ifndef __REDGEMSTONE_H_
#define __REDGEMSTONE_H_
#include "cocos2d.h"
#include "BaseGemstone.h"
using namespace cocos2d;
class RedGemstone:public BaseGemstone{
protected:
	int score;
	int coin;
public:
	virtual bool init(std::string fileName,int r_id_x,int r_id_y);
	static RedGemstone * create(std::string fileName,int r_id_x,int r_id_y);
    virtual std::string sendCast();
};
#endif
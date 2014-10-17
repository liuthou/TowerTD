#ifndef __YELLOWGEMSTONE_H_
#define __YELLOWGEMSTONE_H_
#include "cocos2d.h"
#include "BaseGemstone.h"
class YellowGemstone:public BaseGemstone{
protected:
	int score;
	int coin;
public:
	virtual bool init(std::string fileName, int r_id_x, int r_id_y);
	static YellowGemstone * create(std::string fileName, int r_id_x, int r_id_y);
    virtual std::string sendCast();
};
#endif

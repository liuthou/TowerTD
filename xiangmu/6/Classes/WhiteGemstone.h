#ifndef __WHITEGEMSTONE_H_
#define __WHITEGEMSTONE_H_
#include "cocos2d.h"
#include "BaseGemstone.h"
class WhiteGemstone:public BaseGemstone{
protected:
	int score;
	int coin;
public:
	virtual bool init(std::string fileName,int r_id_x,int r_id_y);
	static WhiteGemstone * create(std::string fileName,int r_id_x,int r_id_y);
    virtual std::string sendCast();
}; 
#endif
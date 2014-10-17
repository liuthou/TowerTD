#ifndef __BASEGEMSTONE_H_
#define __BASEGEMSTONE_H_
#include "cocos2d.h"
#include "BaseRewards.h"
using namespace cocos2d;
class BaseGemstone:public BaseRewards{
protected:
	int m_id_x;
	int m_id_y;
public:
	virtual bool init(std::string fileName,int id_x,int id_y);
	static BaseGemstone * create(std::string fileName,int id_x,int id_y);
	void onEnter();
	virtual void addAnimation();
};
#endif
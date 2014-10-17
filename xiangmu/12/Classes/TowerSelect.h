#ifndef __TOWERSELECT_H
#define __TOWERSELECT_H
#include "cocos2d.h"
#include "GameBasic.h"
using namespace cocos2d;
class TowerSelect:public Layer{
	
	int count; // selected tower count
	std::string countLable;
public:
	virtual bool init();
	CREATE_FUNC(TowerSelect);
};
#endif
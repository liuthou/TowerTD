#ifndef __SELECTTOWERLAYER_H
#define __SELECTTOWERLAYER_H
#include "cocos2d.h"

USING_NS_CC;
 
class SelectTowerLayer :public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(SelectTowerLayer);

	//set TowerType
	 
	std::function < void(int towerType)> addTower;
protected:
	 
private:
	Menu* menu;
 
};
#endif
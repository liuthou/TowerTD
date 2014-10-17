#ifndef __UPDATELAYER_H
#define __UPDATELAYER_H
#include "cocos2d.h"
#include "BaseTower.h"
USING_NS_CC;

class UpdateLayer: public Layer
{  
	
public:
	virtual bool init( BaseTower *tower);
    static UpdateLayer*create(BaseTower *tower);
	//判断是否显示菜单层
	CC_SYNTHESIZE(bool ,isShowing,IsShowing);
	//检查是否存在菜单层
	void show();
	void unshow();
	//得到塔
	BaseTower * towers;
	//升级所需要的钱
	int upGradeMoney;
	//铲除变卖的钱
	int eradicantMoney;
	//升级标签
	Label * updateLabel;

};
#endif
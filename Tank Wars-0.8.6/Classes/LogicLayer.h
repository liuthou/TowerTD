#ifndef __LOGICLAYER_H
#define __LOGICLAYER_H
#include "cocos2d.h"
USING_NS_CC;
class LogicLayer:public Layer
{ 
	void TankTestBound();//双方坦克碰撞
	void BulletTestBound();
	void bulletEvsT(); //敌军子弹和己方子弹碰撞
	void bulletvsBarrer();//子弹和墙
	void bulletVsEnemy();//己方子弹和敌军
	void bulletVsTank();//敌方子弹和主角
    void checkisDefeated();
	void boundingBox(Vec2 position);//子弹的碰撞检测与地图的墙壁 同时四个点
public:	
	virtual bool init();
	CREATE_FUNC(LogicLayer);
	
	void update(float);
};
#endif // !__LOGICLAYER_H

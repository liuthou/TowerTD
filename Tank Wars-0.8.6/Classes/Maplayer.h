#ifndef __MAPLAYER_H
#define __MAPLAYER_H
#include "cocos2d.h"
USING_NS_CC;

class MapLayer :public Layer{
public: 
	virtual bool init();
	CREATE_FUNC(MapLayer);

	Vec2 getState(int i);

	//检查是否可以有东西 是否可破坏
	bool checkNodeBreak(Vec2 position);
	bool checkIsNode(Vec2 position);
	bool breakNode(Vec2 position);//将该点的精灵移出,因为受到子弹攻击
	//检查是否失败,就是基地有没有被打爆
	bool checkNodeWrite(Vec2 position);//检查是否为水

	int count ;//基地个数
	void failed();//失败调用的方法
	bool isDefeated();
private:
	float offX;//误差,因为地图位置改变过,偏移量其实是x向右移动了960*0.2=192;
	TMXTiledMap* map;//地图的层
	//地图上的对象层与点的集合
	TMXObjectGroup* object;
	Vector<Node*> pointsVector;
	void initPointsVector(float offX);
	TMXLayer* bgLayer;//地图的背景层
	TMXLayer* bossLayer;//地图的boss基地一枪就死


	//转换坐标
	Vec2 converTotileCoord(Vec2 position);//转换为地图坐标
	//Vec2 converToMatrixCoord(Vec2 position);//转换为数组坐标

};
#endif
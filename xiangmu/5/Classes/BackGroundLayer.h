#ifndef __BACKGROUNDLAYER_H_
#define __BACKGROUNDLAYER_H_
#include "cocos2d.h"
USING_NS_CC;
class MapLayer;

class BackgroundLayer : public Layer{

public:
	static BackgroundLayer * create();
protected:
	//远山
	Sprite * farMountain_1;
	Sprite * farMountain_2;
	//远田野
	Sprite * farField_1;
	Sprite * farField_2;
	//氤氲
	Sprite * dense_1;
	Sprite * dense_2;
	Sprite * dense_3;
	//近田野
	Sprite * nearField_1;
	Sprite * nearField_2;
	Sprite * nearField_3;
	//路
	Sprite * road_1;
	Sprite * road_2;
	Sprite * road_3;
	//草
	Sprite * grass_1;
	Sprite * grass_2;
	//地图
	MapLayer * map1;
	MapLayer * map2;
	Vector<Layer *> maps;
protected:
	virtual bool init();
	//加载远山背景
	void addFarMountain();
	//加载远田野
	void addFarField();
	//加载氤氲
	void addDense();
	//加载近田野
	void addNearField();
	//加载路
	void addRoad();
	//加载灌木、电线杆等杂项
	void addSundry();
	//加载草
	void addGrass();
	//远山移动
	void farMountainMove(float t);
	//田野移动
	void fieldMove(float t);
	//氤氲移动
	void denseMove(float t);
	//路移动
	void roadMove(float t);
	//草移动
	void grassMove(float t);
	//加载地图
	void addMap();
	//地图移动
	void mapMove(float t);
	//更换地图
	void changeMap();
};

#endif // !__BACKGROUNDLAYER_H_

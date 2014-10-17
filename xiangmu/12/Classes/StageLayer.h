#ifndef __STAGELAYER_H
#define __STAGELAYER_H
#include "cocos2d.h"
using namespace cocos2d;
class StageLayer:public Layer{

public:

	virtual bool init();
	CREATE_FUNC(StageLayer);
protected:

	// build tower
	void addTower(int towerType);

	//direction to build tower
	void initCanBuild(std::vector<Vec2> points);
private:
	//whether or not to build tower
	bool isBulidTime;

	// where to build
	Vec2 buildPos;

	// the origin of layer
	Vec2 m_origin;

	// the tower type
};
#endif
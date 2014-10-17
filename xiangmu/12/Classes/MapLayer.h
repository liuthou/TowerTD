#ifndef __MAPLAYER_H
#define __MAPLAYER_H
#include "cocos2d.h"
using namespace cocos2d;
class MapLayer :public Layer{
public:
	virtual bool init();
	CREATE_FUNC(MapLayer);


	/* some interface for other layers */

	//check is this position for buliding Tower
	bool isCanBulid(Vec2 position);

	//get relative position for tower
	Vec2 getMapPos(Vec2 position);

	//get points of the map object layer 
	std::vector<Vec2>getPoints();

	//when init scene useing
	std::vector<Vec2>getAllCanBuild();
protected:

	//convert to this map position
	Vec2 convertToTitleMap(Vec2 position);

private:
	Vec2 m_origin;
	 
	std::vector<std::vector<Vec2>> allpoints;
	//TMXTitleMap
	TMXTiledMap* map;
	//Sprite bg
	Sprite* map_bg;
	//TMXLayer 
	TMXLayer* layer;
	//TMXObjectGroup
	TMXObjectGroup* obj;

	std::vector<Vec2> allCanBuildPoints;
};
#endif
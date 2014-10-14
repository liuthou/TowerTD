#include "MapLayer.h"
#include "GameManager.h"

bool MapLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto res = GameManager::getInstance()->resources;
	//add maplayer's background
	map_bg = Sprite::create(res.at("bg").asString());

	//set size for this layer equaling the background 

	this->setContentSize(map_bg->getContentSize());
	map_bg->setAnchorPoint(Vec2::ZERO);

	//map_bg->setNormalizedPosition(Vec2(0.5, 0.5));

	this->addChild(map_bg);

	//add maplayer's TMX_map
	map = TMXTiledMap::create(res.at("map").asString());
	//map->setPosition(map_bg->getPosition());
	this->addChild(map);

	//get TMXLayer
	layer = map->getLayer("Tower");

	//get TMXObject
	obj = map->getObjectGroup("path");

	//test points
	std::vector<Vec2> points = getPoints();
	return true;
}
//convert to this map position
Vec2 MapLayer::convertToTitleMap(Vec2 position)
{
	int x = (position.x - map->getPositionX()) / map->getContentSize().width*map->getMapSize().width;
	int y = map->getMapSize().height - (position.y) / map->getContentSize().height*map->getMapSize().height;
	return Vec2(x, y);
}

//check is this position for buliding Tower
bool MapLayer::isCanBulid(Vec2 position)
{
	//get the gid of position
	Vec2 map_pos = convertToTitleMap(position);
	if (map_pos.x < 0 || map_pos.y < 0 || map_pos.x >= 32 || map_pos.y >= 16)
	{
		return false;
	}
	int gid = layer->getTileGIDAt(map_pos);

	Value * value_tmp;
	if (map->getPropertiesForGID(gid, &value_tmp))
	{
		return true;
	}
	return false;

}

//get points of the map object layer 
std::vector<Vec2> MapLayer::getPoints()
{
	
	//1. define a points of Vec2 vector
	 
/*	std::vector<Vec2> points;*/
	int size = allpoints.size();
	if (size > 0)
	{
		int randPoints = (int)(rand()) % size;
		return allpoints.at(randPoints);
	}
	else
	{



// 	if (points.size() > 0 && points_t.size() > 0 && points_r.size() > 0 && points_s.size() > 0 && points_f.size() > 0 && points_v.size() > 0)
// 	{
// 		int randPoints = (int)(rand()) % 6;
// 		if (randPoints == 1)
// 		{
// 			return points;
// 		}else if (randPoints == 2)
// 		{
// 			return points_t;
// 		}
// 		else if (randPoints == 3)
// 		{
// 			return points_r;
// 		}
// 		else if (randPoints == 4)
// 		{
// 			return points_f;
// 		}
// 		else if (randPoints == 5)
// 		{
// 			return points_v;
// 		}
// 		return points_s;
// 	}
	// 	int count = 1;	
	// 	ValueMap temp;
	// 	temp = obj->getObject(std::to_string(count));
	
	/*1. get points */
		std::vector<Vec2> points;
		//2. get all points of obj
	ValueVector objects = obj->getObjects();

		//3.  traverse all point and add it to points
	for (Value value : objects)
	{
		ValueMap temp = value.asValueMap();
		Vec2 point;
		point.x = temp.at("x").asFloat();
		point.y = temp.at("y").asFloat();
		points.push_back(point);
	}
	allpoints.push_back(points);
		//get TMXObject
	/*2. get points_t*/
	std::vector<Vec2> points_t;
	auto obj_t = map->getObjectGroup("path_t");
	if (obj_t)	 
	{ 
		ValueVector objects_t = obj_t->getObjects();

		//3.  traverse all point and add it to points
		for (Value value : objects_t)
		{
			ValueMap temp = value.asValueMap();
			Vec2 point;
			point.x = temp.at("x").asFloat();
			point.y = temp.at("y").asFloat();
			points_t.push_back(point);
		}
		allpoints.push_back(points_t);
	}
	/*3. get points_r*/
	std::vector<Vec2> points_r;
	auto obj_r = map->getObjectGroup("path_r");
	if (obj_r)
	{
		ValueVector objects_r = obj_r->getObjects();
		//3.  traverse all point and add it to points
		for (Value value : objects_r)
		{
			ValueMap temp = value.asValueMap();
			Vec2 point;
			point.x = temp.at("x").asFloat();
			point.y = temp.at("y").asFloat();
			points_r.push_back(point);
		}
		allpoints.push_back(points_r);
	}
	/*4. get points_s*/
	std::vector<Vec2> points_s;
	auto obj_s = map->getObjectGroup("path_s");
	if (obj_s) 
	{
		ValueVector objects_s = obj_s->getObjects();
		//3.  traverse all point and add it to points
		for (Value value : objects_s)
		{
			ValueMap temp = value.asValueMap();
			Vec2 point;
			point.x = temp.at("x").asFloat();
			point.y = temp.at("y").asFloat();
			points_s.push_back(point);
		}
		allpoints.push_back(points_s);
	}
	/*5. get points_f*/
	std::vector<Vec2> points_f;
	auto obj_f = map->getObjectGroup("path_f");
	if (obj_f) 
	{
		ValueVector objects_f = obj_f->getObjects();
		//3.  traverse all point and add it to points
		for (Value value : objects_f)
		{
			ValueMap temp = value.asValueMap();
			Vec2 point;
			point.x = temp.at("x").asFloat();
			point.y = temp.at("y").asFloat();
			points_f.push_back(point);
		}
		allpoints.push_back(points_f);
	}
	/*6. get points_v*/
	std::vector<Vec2> points_v;
	auto obj_v = map->getObjectGroup("path_v");
	if (obj_v) 
	{
		ValueVector objects_v = obj_v->getObjects();
		//3.  traverse all point and add it to points
		for (Value value : objects_v)
		{
			ValueMap temp = value.asValueMap();
			Vec2 point;
			point.x = temp.at("x").asFloat();
			point.y = temp.at("y").asFloat();
			points_v.push_back(point);
		}
		allpoints.push_back(points_v);
	}
		}
		//return points;
		int randPoints = (int)(rand()) %allpoints.size();
		return allpoints.at(randPoints);
}

//get right psition for tile of map
Vec2 MapLayer::getMapPos(Vec2 position)
{
	position = convertToTitleMap(position);

	auto tileWidth = map->getContentSize().width / map->getMapSize().width;
	auto tileHeight = map->getContentSize().height / map->getMapSize().height;

	Vec2 towerPos = Point((position.x * tileWidth) + tileWidth / 2, map->getContentSize().height - (position.y * tileHeight) + tileHeight / 2);
	return towerPos;
}
// for scene init points
std::vector<Vec2> MapLayer::getAllCanBuild()
{
	
	if (!allCanBuildPoints.empty())
	{
		return allCanBuildPoints;
	}
	int i = 0;	
	while (i<32){
		int j = 0;
		while (j < 16){
			Vec2 map_pos = Vec2(i, j);

			int gid = layer->getTileGIDAt(map_pos);

			if (gid)
			{
				map_pos = Vec2(map_pos.x * 64, (16 - map_pos.y - 1) * 64);
				map_pos = this->getMapPos(map_pos);
				allCanBuildPoints.push_back(map_pos);
			} 
			j++;
		}
		i++;
	}
	 
	return allCanBuildPoints;
}
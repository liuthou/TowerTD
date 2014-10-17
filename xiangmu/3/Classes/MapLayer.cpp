#include "MapLayer.h"
#include "MainScene.h"
bool MapLayer::init(){
	if (!Layer::init()){
		return false;
	}
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size size = Director::getInstance()->getVisibleSize();
	this->setTiledMap(TMXTiledMap::create("map.tmx"));
//	map->setAnchorPoint(Vec2(0,0));
	Size mapsize = map->getContentSize();
	map->setPosition(origin.x+size.width/2-mapsize.width/2,origin.y+size.height/2-mapsize.height/2);
	this->addChild(map);
	this->setBackground(map->getLayer("bg"));
	return true;
}
Vec2 MapLayer::convertTilesPositionToVisiblePosition(Vec2 pointoftiles){//将地图坐标转换为屏幕坐标
	Vec2 visableposition;
	Vec2 mapposition = map->getPosition();
	visableposition.x = pointoftiles.x * TILEDSIZE+mapposition.x;
	visableposition.y = (PIECENUM.y - pointoftiles.y )*TILEDSIZE+mapposition.y;
	return visableposition;
}
Vec2 MapLayer::convertVisiblePositionToTilesPosition(Vec2 pointofview){//将屏幕坐标转换为图上坐标
	Vec2 mapposition = map->getPosition();
	Vec2 tiledposition;
	tiledposition.x = (int)(pointofview.x - mapposition.x)/TILEDSIZE;
	tiledposition.y = PIECENUM.y - (int)(pointofview.y - mapposition.y)/TILEDSIZE - 1;
	return tiledposition;
}
Vec2 MapLayer::setSPPositOfTiled(Vec2 pointofview){ //根据屏幕坐标设置精灵所在地图上图块位置
	Vec2 mapposition = map->getPosition();
	Vec2 tPosition;
	tPosition.x = ((int)(pointofview.x - mapposition.x)/TILEDSIZE + 1)*TILEDSIZE + mapposition.x - TILEDSIZE/2 ;
	tPosition.y = ((int)(pointofview.y - mapposition.y)/TILEDSIZE + 1)*TILEDSIZE + mapposition.y - TILEDSIZE/2 ;
	return tPosition;
}

bool MapLayer::hasTower(Vec2 pointofworld){
	Vec2 pointofmap=convertVisiblePositionToTilesPosition(pointofworld);
	Rect maprect=map->getBoundingBox();
	if (pointofmap.x<=0||pointofmap.x >= map->getMapSize().width||pointofmap.y<=0||pointofmap.y >= map->getMapSize().height){
		return false;
	}
	int bggid = background->getTileGIDAt(Vec2(pointofmap.x ,pointofmap.y ));
	Value *vp = nullptr;
	if (map->getPropertiesForGID(bggid,&vp)){
		auto vm = vp->asValueMap();
		if (vm.find("couldtower")!=vm.end())
		{
			auto val = vm.at("couldtower");
			if (bggid&&val.asString() == "true"){
				return true;
			}
		}
	}
	return false;
	
}

bool MapLayer::isInMap(Vec2 pointofworld){
	Vec2 pointofmap=convertVisiblePositionToTilesPosition(pointofworld);
	Rect maprect=map->getBoundingBox();
	if (pointofmap.x<0||pointofmap.x > map->getMapSize().width||pointofmap.y<0||pointofmap.y > map->getMapSize().height){
		return false;
	}
	return true;
}

void MapLayer::changeGID(Vec2 towerPosition){//根据地图坐标更改GID
	MainScene *mScene = dynamic_cast<MainScene *>(Director::getInstance()->getRunningScene());
	auto mapLayer = mScene->getMapLayer();
	auto mapBg = mapLayer->getBackground();
	auto mPosition = mapLayer->convertVisiblePositionToTilesPosition(towerPosition);
	int gid = mapBg->getTileGIDAt(mPosition);
	if (gid == 1){
		mapBg->setTileGID(3,Vec2(mPosition));
	}
}

void MapLayer::removeGID(Vec2 towerPosition){
	MainScene *mScene = dynamic_cast<MainScene *>(Director::getInstance()->getRunningScene());
	auto mapLayer = mScene->getMapLayer();
	auto mapBg = mapLayer->getBackground();
	auto mPosition = mapLayer->convertVisiblePositionToTilesPosition(towerPosition);
	int gid = mapBg->getTileGIDAt(mPosition);
	if (gid == 3){
		mapBg->setTileGID(1,Vec2(mPosition));
	}
}

bool MapLayer::couldPass(Vec2 pointofworld){
	Rect maprect=map->getBoundingBox();
	if (pointofworld.x<maprect.getMinX()||pointofworld.x > maprect.getMaxX()||pointofworld.y<maprect.getMinY()||pointofworld.y > maprect.getMaxY()){
		return false;
	}
	Vec2 pointofmap=convertVisiblePositionToTilesPosition(pointofworld);
	int bggid = background->getTileGIDAt(Vec2(pointofmap.x ,pointofmap.y ));
	Value *vp = nullptr;
	if (map->getPropertiesForGID(bggid,&vp)){
		auto vm = vp->asValueMap();
		if (vm.find("couldpass")!=vm.end())
		{
			auto val = vm.at("couldpass");
			if (val.asString() == "true"){
				return true;
			}
		}
	}
	return false;
}

std::vector<Vec2> MapLayer::enemyBurnPosition(){
	std::vector<Vec2> burnpoints;

	TMXObjectGroup *group = map->getObjectGroup("object");
	ValueVector burngroup = group->getObjects();
	
	for (auto it = burngroup.begin();it<burngroup.end();it++){
		ValueMap tmpvalue = it->asValueMap();
		if (tmpvalue.find("name")!=tmpvalue.end())
		{
			std::string name = "monterburn";
			if (tmpvalue.at("name").asString() == name)
			{
				Vec2 tmpposition;
				tmpposition.x = tmpvalue.at("x").asFloat();
				tmpposition.y = tmpvalue.at("y").asFloat();
				tmpposition+=map->getPosition();
				burnpoints.push_back(tmpposition);
			}
		}
	}

		return burnpoints;
}
Vec2 MapLayer::MonstEndPosition(){;//怪物终位置
	TMXObjectGroup *group = map->getObjectGroup("object");
	auto endPositioninfo = group->getObject("home");
	float x = endPositioninfo.at("x").asFloat();
	float y = endPositioninfo.at("y").asFloat();
	Vec2 endPosition = Vec2(x,y);
	endPosition+=map->getPosition();
	return endPosition;
}
Vec2 MapLayer::getMapSizeInPixel(){
	return map->getContentSize();
}
Vec2 MapLayer::getMapPosition(){
	return map->getPosition();
}

#ifndef __MAPLAYER_H_
#define __MAPLAYER_H_
#include "cocos2d.h"
#define  TILEDSIZE  64              //图块尺寸
#define  MAPPOSITION Vec2(0,0)    //地图的位置
#define  PIECENUM Vec2(10,15)        //图块个数
USING_NS_CC;
class MapLayer:public Layer{
public:
	CREATE_FUNC(MapLayer);
	virtual bool init();
	Vec2 convertTilesPositionToVisiblePosition(Vec2 pointoftiles);
	Vec2 setSPPositOfTiled(Vec2 pointofview);
	Vec2 convertVisiblePositionToTilesPosition(Vec2 pointofview);
	//能否通过
	bool couldPass(Vec2 pointofworld);
	//是否有塔
	bool hasTower(Vec2 pointofworld);
	//添加塔
	void changeGID(Vec2 towerPosition);
	//删除塔
	void removeGID(Vec2 towerPosition);
	//是否在地图内
	bool isInMap(Vec2 pointofworld);
	Point getPositionofTiles(Point pointofworld);
	Vec2 getMapSizeInPixel();
	Vec2 getMapPosition();
	Vec2 MonstEndPosition();//怪物终位置->造成伤害
	//怪物出生位置
	std::vector<Vec2> enemyBurnPosition();
	CC_SYNTHESIZE_RETAIN(TMXTiledMap *,map,TiledMap);
	CC_SYNTHESIZE_RETAIN(TMXLayer*,background,Background);
protected:
	Size mapsize;
	Size tilessize;
	Size mapcontentsize;
	Vec2 mapposition;
	MapLayer(){
		map=nullptr;
		background=nullptr;
	}
	virtual~MapLayer(){
		CC_SAFE_RELEASE_NULL(map);
		CC_SAFE_RELEASE_NULL(background);
	}
};
#endif
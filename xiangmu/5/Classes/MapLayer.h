#ifndef __MAPLAYER_H_
#define __MAPLAYER_H_
#include "BaseSprite.h"
#include "cocos2d.h"
USING_NS_CC;

class MapLayer : public Layer{
public:
	static MapLayer * create(int mapNum);
protected:
	virtual bool init(int mapNum);
private:
	TMXTiledMap *tiledMap;
	void addObject(std::string layerName,int layerType);
};

#endif // !__MAPLAYER_H_

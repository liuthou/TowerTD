//
//  MapUtil.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __CarrotFantasy__MapUtil__
#define __CarrotFantasy__MapUtil__

#include "PublicDefine.h"

class MapUtil: public Ref
{
public:
    
    CREATE_INSTANCE_FUNC(MapUtil);
    
    DESTROY_INSTANCE_FUNC();
    
    virtual void setCurrentLevelTiledMap(TMXTiledMap *pTiledMap);
    
    virtual std::vector<Vec2> getMovePoses();
    
    virtual std::vector<std::pair<std::string, Rect>> getBarrierPoses();
    
    virtual std::vector<Rect> getEffectTowerPoses();
    
    virtual void removeBarrierRect(const Vec2 &rPos);
    
protected:
    
    virtual bool init();
    
    virtual void clearMap();
    
    virtual void rectTransVec(const Rect &rRect);
    
private:
    
    TMXTiledMap *_pTildeMap = nullptr;
    
    std::map<int, Vec2> *_pMovePosMap = nullptr;
    
    std::vector<std::pair<std::string, Rect>> *_pBarrierPosMap = nullptr;
    
    std::vector<Rect> *_pEffectTowerRectVec = nullptr;
    
private:
    
    Size _gridSize;
    Size _mapSize;
    
private:
    
    virtual ~MapUtil();
    
};


#endif /* defined(__CarrotFantasy__MapUtil__) */

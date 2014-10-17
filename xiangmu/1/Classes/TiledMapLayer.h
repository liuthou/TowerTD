//
//  TiledMapLayer.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __CarrotFantasy__TiledMapLayer__
#define __CarrotFantasy__TiledMapLayer__

#include "cocos2d.h"
using namespace cocos2d;

/**
 *  TiledMapLayer use to load tmx map and bg
 */

class TiledMapLayer: public Layer
{
public:
    
    CREATE_FUNC(TiledMapLayer);
    
protected:
    
    virtual bool init();
    
    virtual void loadSource();

private:
    
    TMXTiledMap *_pTiledMap = nullptr;
};

#endif /* defined(__CarrotFantasy__TiledMapLayer__) */

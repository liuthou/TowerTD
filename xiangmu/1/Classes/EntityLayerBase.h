//
//  LayerBase.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-16.
//
//

#ifndef __CarrotFantasy__EntityLayerBase__
#define __CarrotFantasy__EntityLayerBase__

#include "cocos2d.h"
using namespace cocos2d;

class Entity;

class EntityLayerBase:public Layer
{
    
public:
    
    virtual void addEntity(Entity *pEntity);
};

#endif /* defined(__CarrotFantasy__LayerBase__) */

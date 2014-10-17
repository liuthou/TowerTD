//
//  LayerBase.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-9-16.
//
//

#include "EntityLayerBase.h"
#include "Entity.h"

void EntityLayerBase::addEntity(Entity *pEntity)
{
    addChild(pEntity);
}
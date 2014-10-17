//
//  TowerFactory.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __CarrotFantasy__TowerFactory__
#define __CarrotFantasy__TowerFactory__

#include "PublicDefine.h"

class TowerBase;

class TowerFactory
{
public:
    static TowerBase *createTower(const TowerType &rTowerType, Vec2 tPosition);
};

#endif /* defined(__CarrotFantasy__TowerFactory__) */

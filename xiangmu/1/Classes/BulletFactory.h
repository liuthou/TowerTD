//
//  BulletFactory.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __CarrotFantasy__BulletFactory__
#define __CarrotFantasy__BulletFactory__

#include "PublicDefine.h"

class VictimEntityBase;

class BulletFactory
{
public:
    
	static BulletBase *createBullet(const int &rBulletId, TowerBase* rTower, VictimEntityBase *rVictimEntity);
};

#endif /* defined(__CarrotFantasy__BulletFactory__) */

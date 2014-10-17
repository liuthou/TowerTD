//
//  CollisionManager.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __CarrotFantasy__CollisionManager__
#define __CarrotFantasy__CollisionManager__

#include "PublicDefine.h"

class CollisionManager
{
public:
    
    static void collision(Vector<BarrierBase *> &rBarrierVec, Vector<MonsterBase *> &rMonsterVec, Vector<BulletBase*> &rBulletVec);
	
protected:
	/**
	 * the Collision between Monsters and Bullets 
	 */
	static void MonsterAndBullet(BulletBase * pBullet, Vector<MonsterBase *> &rMonsterVec);
	/**
	 * the Collision between Barriers and bullets
	 */
	static void BarrierAndBullet(BulletBase * pBullet,Vector<BarrierBase *> &rBarrierVec);
	/**
	 * just make the Animation
	 */
	static Animation * AnimationMaker(std::string BulletName,int SpriteFrameCount);
    
};

#endif /* defined(__CarrotFantasy__CollisionManager__) */

//
//  MonsterLayer.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __CarrotFantasy__MonsterLayer__
#define __CarrotFantasy__MonsterLayer__

#include "EntityLayerBase.h"

class MonsterBase;

/**
 *  monsterLayer use to show Monster
 */

class MonsterLayer:public EntityLayerBase
{
public:
    
    CREATE_FUNC(MonsterLayer);
    
protected:
    
    virtual bool init();
    
    virtual void registerMonsterDeadEvent();
    
    virtual void monsterDead(Ref *pData);
    
    virtual void onExit()override;
    
};

#endif /* defined(__CarrotFantasy__MonsterLayer__) */

//
//  MonsterFactory.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __CarrotFantasy__MonsterFactory__
#define __CarrotFantasy__MonsterFactory__

#include "PublicDefine.h"

class MonsterFactory
{
public:
    
    static MonsterBase *createMonster(const MonsterType &rMonsterType);
};

#endif /* defined(__CarrotFantasy__MonsterFactory__) */

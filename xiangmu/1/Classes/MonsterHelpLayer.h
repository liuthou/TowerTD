//
//  MonsterHelpLayer.h
//  CarrotFantasy
//
//  Created by Yan on 14-10-6.
//
//

#ifndef __CarrotFantasy__MonsterHelpLayer__
#define __CarrotFantasy__MonsterHelpLayer__

#include "PublicDefine.h"

class MonsterHelpLayer:public Layer
{
public:
    
    CREATE_FUNC(MonsterHelpLayer);
    
protected:
    
    virtual bool init()override;
};

#endif /* defined(__CarrotFantasy__MonsterHelpLayer__) */

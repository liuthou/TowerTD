//
//  BulletsLayer.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __CarrotFantasy__BulletsLayer__
#define __CarrotFantasy__BulletsLayer__

#include "EntityLayerBase.h"

/**
 *  BulletsLayer use to show Bullet
 */

class BulletsLayer:public EntityLayerBase
{
public:
    
    CREATE_FUNC(BulletsLayer);
    
protected:
    
    virtual bool init();
    
    virtual void update(float dt);
};

#endif /* defined(__CarrotFantasy__BulletsLayer__) */

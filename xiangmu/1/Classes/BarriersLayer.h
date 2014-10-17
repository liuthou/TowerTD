//
//  BarriersLayer.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __CarrotFantasy__BarriersLayer__
#define __CarrotFantasy__BarriersLayer__

#include "EntityLayerBase.h"

/**
 *  BarriersLayer use to show barrier
 */

class BarriersLayer: public EntityLayerBase
{
    
public:
    
    CREATE_FUNC(BarriersLayer);
    
protected:
    
    virtual bool init();
    
};

#endif /* defined(__CarrotFantasy__BarriersLayer__) */

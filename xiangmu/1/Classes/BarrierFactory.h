//
//  BarrierFactory.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __CarrotFantasy__BarrierFactory__
#define __CarrotFantasy__BarrierFactory__

#include "PublicDefine.h"

class BarrierBase;

class BarrierFactory
{
public:
    static BarrierBase *createBarrier(const BarrierType &rBarrierType);
};

#endif /* defined(__CarrotFantasy__BarrierFactory__) */

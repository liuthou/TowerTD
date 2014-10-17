//
//  BarriersLayer.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#include "BarriersLayer.h"

bool BarriersLayer::init()
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!EntityLayerBase::init());
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}





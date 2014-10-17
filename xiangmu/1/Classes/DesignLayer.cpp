//
//  DesignLayer.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#include "DesignLayer.h"



bool DesignLayer::init()
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Layer::init());
        
        loadSource();
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void DesignLayer::loadSource()
{
    auto pBg = Sprite::create("./Themes/credits_bg.png");
    addChild(pBg);
}
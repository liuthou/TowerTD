//
//  DataCollectLayer.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#include "DataCollectLayer.h"


bool DataCollectLayer::init()
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

void DataCollectLayer::loadSource()
{
    auto pBg = Sprite::createWithSpriteFrameName("statistics_bg.png");
    addChild(pBg);
}
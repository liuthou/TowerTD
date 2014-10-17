//
//  SceneBase.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-9-23.
//
//

#include "SceneBase.h"

void SceneBase::sourceManager(const std::vector<std::string> &rSourceNameVec, const bool &rBLoad)
{
    auto pSpriteFrameCache = SpriteFrameCache::getInstance();
    for(auto &iterSourceName : rSourceNameVec)
    {
        if(rBLoad)  pSpriteFrameCache->addSpriteFramesWithFile(iterSourceName + PLISTPOSTFIX, iterSourceName + PHOTOPOSTFIX);
        else pSpriteFrameCache->removeSpriteFramesFromFile(iterSourceName + PLISTPOSTFIX);
    }
}

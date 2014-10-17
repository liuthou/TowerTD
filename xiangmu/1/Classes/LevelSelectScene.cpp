//
//  LevelSelectScene.cpp
//  newCardDefence
//
//  Created by Yan on 14-9-12.
//
//

#include "LevelSelectScene.h"
#include "LevelSelectLayer.h"
#include "SceneManager.h"

LevelSelectScene::~LevelSelectScene()
{
    CC_SAFE_RELEASE_NULL(_pLevelSelectLayer);
    sourceManager(std::vector<std::string>{THEMESSOURCE[_iThemeIndex]}, false);
    
}

bool LevelSelectScene::init()
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Scene::init());
        _iThemeIndex = SceneManager::getInstance()->getCurPageIndex();
        sourceManager(std::vector<std::string>{THEMESSOURCE[_iThemeIndex]}, true);
        
        _pLevelSelectLayer = LevelSelectLayer::create();
        _pLevelSelectLayer->retain();
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void LevelSelectScene::onEnter()
{
    Scene::onEnter();
    addChild(_pLevelSelectLayer);
}




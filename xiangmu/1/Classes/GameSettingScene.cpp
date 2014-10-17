//
//  GameSettingScene.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#include "GameSettingScene.h"
#include "TopPanelLayer.h"

GameSettingScene::~GameSettingScene()
{
    CC_SAFE_RELEASE_NULL(_pPanelLayer);
}

bool GameSettingScene::init()
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Scene::init());
    
        _pPanelLayer = TopPanelLayer::create();
        _pPanelLayer->retain();
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void GameSettingScene::onEnter()
{
    Scene::onEnter();

    addChild(_pPanelLayer);
}






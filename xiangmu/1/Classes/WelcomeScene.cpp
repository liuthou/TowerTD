//
//  WelcomeScene.cpp
//  newCardDefence
//
//  Created by Yan on 14-8-27.
//
//

#include "WelcomeScene.h"
#include "SpritesLayer.h"
#include "MenusLayer.h"
#include "LoadingSourceLayer.h"
#include "Config.h"

WelcomeScene::~WelcomeScene()
{
    CC_SAFE_RELEASE_NULL(_pMenusLayer);
    CC_SAFE_RELEASE_NULL(_pSpritesLayer);
}

bool WelcomeScene::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Scene::init());
        
        _pSpritesLayer = SpritesLayer::create();
        _pSpritesLayer->retain();
        
        _pMenusLayer = MenusLayer::create();
        _pMenusLayer->retain();
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void WelcomeScene::onEnter()
{
    Scene::onEnter();
    addChild(_pSpritesLayer);

    if(!Config::getInstance()->getIsLoadSource())
    {
        auto pLoadingLayer = LoadingSourceLayer::create();
        pLoadingLayer->setFuncShowMenuPanel(CC_CALLBACK_0(WelcomeScene::showMenu, this));
        pLoadingLayer->setName("loadingLayer");
        addChild(pLoadingLayer);
    }
    else
    {
        addChild(_pMenusLayer);
    }
}


void WelcomeScene::showMenu()
{
    getChildByName("loadingLayer")->removeFromParent();
    addChild(_pMenusLayer);
	Config::getInstance()->setIsLoadSource(true);
}





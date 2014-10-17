//
//  LevelSelectScene.cpp
//  newCardDefence
//
//  Created by Yan on 14-8-27.
//
//

#include "PageSelectScene.h"
#include "PageViewLayer.h"
#include "MenuPanelLayer.h"

PageSelectScene::~PageSelectScene()
{
    CC_SAFE_RELEASE_NULL(_pPageViewLayer);
    CC_SAFE_RELEASE_NULL(_pMenuPanelLayer);
}

bool PageSelectScene::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Scene::init());

        _pPageViewLayer = PageViewLayer::create();
        _pPageViewLayer->retain();
        
        _pMenuPanelLayer = MenuPanelLayer::create();
        _pMenuPanelLayer->retain();
        
        auto pMenuPanelLayer = dynamic_cast<MenuPanelLayer*>(_pMenuPanelLayer);
        pMenuPanelLayer->setPageTurnFunc(CC_CALLBACK_1(PageViewLayer::pageTurn, dynamic_cast<PageViewLayer*>(_pPageViewLayer)));
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void PageSelectScene::onEnter()
{
    Scene::onEnter();
    addChild(_pPageViewLayer);
    addChild(_pMenuPanelLayer);
}


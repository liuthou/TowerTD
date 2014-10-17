//
//  LoadingScene.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-10-3.
//
//

#include "LoadingScene.h"
#include "GameScene.h"
#include "SoundUtil.h"

bool LoadingScene::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Scene::init());
        
        auto pBg = Sprite::create(LOADINGSOURCE);
        pBg->setPosition(VisibleRect::center());
        addChild(pBg);
    
        bRet = true;
    }
    while (0);
    return bRet;
}

void LoadingScene::onEnter()
{
    Scene::onEnter();
    SoundUtil::getInstance()->stopBackGroundSound();
    NOTIFY->addObserver(this, callfuncO_selector(LoadingScene::sourceLoadCallBack), "loadFinish", nullptr);
    _pGameScene = GameScene::create();
    _pGameScene->retain();
}

void LoadingScene::onExit()
{
    NOTIFY->removeAllObservers(this);
    CC_SAFE_RELEASE_NULL(_pGameScene);
    Scene::onExit();
}

void LoadingScene::sourceLoadCallBack(Ref *pData)
{
    auto pTransScene = TransitionFade::create(0.2f, dynamic_cast<Scene*>(pData));
    Director::getInstance()->replaceScene(pTransScene);
}

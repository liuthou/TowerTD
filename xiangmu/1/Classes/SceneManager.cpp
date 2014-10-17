//
//  SceneManager.cpp
//  newCardDefence
//
//  Created by Yan on 14-8-27.
//
//

#include "SceneManager.h"
#include "SceneFactory.h"
#include "SoundUtil.h"

SceneManager *SceneManager::_gInstance;

bool SceneManager::init()
{
    bool bRet = false;
    do
    {
        registerChangeSceneEvent();
        
        bRet = true;
    }
    while (0);
    return bRet;
}

void SceneManager::initWelComeScene()
{
    auto enCurScene = std::make_tuple(_enCurScene, 0);
    changeScene(enCurScene);
}

void SceneManager::unRegisterAllEvent()
{
    NOTIFY->removeAllObservers(this);
}

void SceneManager::changeScene(const std::tuple<SceneType, int> &rEnSceneType)
{
    Director::getInstance()->getScheduler()->setTimeScale(1);
    
    auto tSceneType = std::get<0>(rEnSceneType);
    
    if(en_GameScene == tSceneType) _iCurLevelIndex = std::get<1>(rEnSceneType);
    
    if(en_LevelSelectScene == tSceneType) _iCurPageIndex = std::get<1>(rEnSceneType);
    
    if(en_GameScene != tSceneType) SoundUtil::getInstance()->playBackgroundSound(BACKGROUNDSOUND.c_str());
    
    checkCurPageAndLevel();
    
    auto pScene = SceneFactory::createScene(tSceneType);
//    auto pTransScene = TransitionFade::create(0.2f, pScene);
    
    auto pDirector = Director::getInstance();
    auto pRunScene = pDirector->getRunningScene();
    
//    pRunScene ? pDirector->replaceScene(pTransScene) : pDirector->runWithScene(pTransScene);
    pRunScene ? pDirector->replaceScene(pScene) : pDirector->runWithScene(pScene);
}

void SceneManager::checkCurPageAndLevel()
{
    auto tCurPageLevelCount = THEME_LEVELCOUNT_ARRAY[_iCurPageIndex];
    if(tCurPageLevelCount == _iCurLevelIndex)
    {
        ++_iCurPageIndex;
        _iCurLevelIndex = 0;
    }
}

void SceneManager::notifyChangeScene(Ref *pData)
{
    auto enSceneType = *(reinterpret_cast<std::tuple<SceneType, int> *>(pData));
    changeScene(enSceneType);
}

void SceneManager::registerChangeSceneEvent()
{
    NOTIFY->addObserver(this, callfuncO_selector(SceneManager::notifyChangeScene), "changeScene", nullptr);
}

int SceneManager::getCurPageIndex()const
{
    return _iCurPageIndex;
}

int SceneManager::getCurLevelIndex()const
{
    return _iCurLevelIndex;
}






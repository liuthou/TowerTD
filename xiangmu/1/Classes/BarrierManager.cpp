//
//  BarrierManager.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#include "BarrierManager.h"
#include "BarrierBase.h"
#include "SceneManager.h"

BarrierManager *BarrierManager::_gInstance;

BarrierManager::BarrierManager()
{
}

BarrierManager::~BarrierManager()
{
    CC_SAFE_DELETE(_pBarrierVec);
}


bool BarrierManager::init()
{
    bool bRet = false;
    
    do
    {
        _pBarrierVec = new Vector<BarrierBase*>();
        registerBarrierDeadEvent();
        bRet = true;
    }
    while (0);
    
    return bRet;
}

Vector<BarrierBase*> &BarrierManager::getBarrierVec()
{
    return *_pBarrierVec;
}

void BarrierManager::addBarrier(BarrierBase *pBarrier)
{
    if(_pBarrierVec) _pBarrierVec->pushBack(pBarrier);
    _funcAddBarrierToLayer(pBarrier);
}

void BarrierManager::setFuncAddBarrierToLayer(const std::function<void (Entity *)> &rFuncAddBarrierToLayer)
{
    _funcAddBarrierToLayer = rFuncAddBarrierToLayer;
}

void BarrierManager::registerBarrierDeadEvent()
{
    NOTIFY->addObserver(this, callfuncO_selector(BarrierManager::removeBarrierFromManager), "BarrierDead", nullptr);
}

void BarrierManager::removeBarrierFromManager(Ref *pBarrier)
{
    if(!(_pBarrierVec && _pBarrierVec->size())) return;
    _pBarrierVec->eraseObject(reinterpret_cast<BarrierBase*>(pBarrier));
    
    if(!_pBarrierVec->size())
    {
        auto tThemeIndex = SceneManager::getInstance()->getCurPageIndex() + 1;
        auto tLevelIndex = SceneManager::getInstance()->getCurLevelIndex() + 1;
        auto tLevelData = std::make_tuple(1, 1, tThemeIndex, tLevelIndex);
        NOTIFY->postNotification(LEVELDATACHANGE, reinterpret_cast<Ref*>(&tLevelData));
    }
}

void BarrierManager::clearManager()
{
    _pBarrierVec->clear();
}

void BarrierManager::clearBeAtkLockState()
{
    for(auto &iterBarrier : *_pBarrierVec)
        iterBarrier->setAtkTarget(false);
}




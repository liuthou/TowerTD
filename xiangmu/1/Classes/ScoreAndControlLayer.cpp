//
//  ScoreAndControlLayer.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#include "ScoreAndControlLayer.h"
#include "PauseLayer.h"
#include "NumSprite.h"
#include "LevelConfigUtil.h"
#include "SoundUtil.h"
#include "PublicSourceDefine.h"
#include "MonsterLayer.h"
#include "GameScene.h"
#include "GameManager.h"

bool ScoreAndControllerLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Layer::init());
        
        _iMoney = LevelConfigUtil::getInstance()->getCurLevelMoney();
        
        registerNotifyEvent();
        
        loadBg();
        
        createTopPanel();
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void ScoreAndControllerLayer::loadBg()
{
    auto tVisibleSize = Director::getInstance()->getVisibleSize();
    auto pPanelBg = Sprite::createWithSpriteFrameName("MenuBG.png");
    pPanelBg->setPosition(Vec2(tVisibleSize.width / 2, tVisibleSize.height - pPanelBg->getContentSize().height / 2));
    addChild(pPanelBg);
    
    auto pTitle = Sprite::createWithSpriteFrameName("MenuCenter_01_CN.png");
    pTitle->setPosition(Vec2(tVisibleSize.width / 2, tVisibleSize.height - pTitle->getContentSize().height / 2 - 5));
    addChild(pTitle);
    
    auto tSize = Sprite::create(MONSTERBATCHIMAGE)->getContentSize();
    auto pMonsterBatchCountSprite = NumSprite::createNum(StringUtils::format("%d", LevelConfigUtil::getInstance()->getCurLevelMonsterBatchCount()), MONEYNUMIMAGE);
    addChild(pMonsterBatchCountSprite);
    auto tScreenSize = Director::getInstance()->getVisibleSize();
    pMonsterBatchCountSprite->setPosition(tScreenSize.width / 2, 603);
    pMonsterBatchCountSprite->release();

    _pMoneyLabel = NumSprite::createNum(StringUtils::format("%d", _iMoney), MONEYNUMIMAGE);
    addChild(_pMoneyLabel);
    _pMoneyLabel->release();
    _pMoneyLabel->setPosition(100, 603);
    
    _pMonsterBatchIndex = NumSprite::createNum(StringUtils::format("%02d", 1), MONSTERBATCHIMAGE);
    addChild(_pMonsterBatchIndex);
    _pMonsterBatchIndex->release();
    _pMonsterBatchIndex->setPosition(379, 603);
}

void ScoreAndControllerLayer::createTopPanel()
{
    auto pSpeedNormalItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("speed11.png"), Sprite::createWithSpriteFrameName("speed12.png"));
    auto pSpeedDoubleItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("speed21.png"), Sprite::createWithSpriteFrameName("speed22.png"));
    auto pSpeedToggleItem = MenuItemToggle::createWithCallback([&](Ref *pSender)
                                                               {
                                                                   auto pScheduler = Director::getInstance()->getScheduler();
                                                                   _bIsOpenSpeedUp = !_bIsOpenSpeedUp ? true : false;
                                                                   pScheduler->setTimeScale(_bIsOpenSpeedUp ? 2.8 : 1.8);
                                                                   
                                                               },
                                                               pSpeedNormalItem, pSpeedDoubleItem, nullptr);
    pSpeedToggleItem->setPosition(685, 597);
    
    auto pPauseItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("pause01.png"), Sprite::createWithSpriteFrameName("pause02.png"));
    auto pContinueItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("pause11.png"), Sprite::createWithSpriteFrameName("pause12.png"));
    auto pPauseItemToggleItem = MenuItemToggle::createWithCallback([&](Ref *pSender)
    {
        auto pDirector = Director::getInstance()->getInstance();
        pDirector->isPaused() ? pDirector->resume() : pDirector->pause();
        auto pGameManager = GameManager::getInstance();
        pGameManager->setIsPause(!pGameManager->getIsPause());

    }, pPauseItem, pContinueItem, nullptr);
    pPauseItemToggleItem->setPosition(795, 597);
    
    auto pChooseItems = MenuItemSprite::create(Sprite::createWithSpriteFrameName("menu01.png"), Sprite::createWithSpriteFrameName("menu02.png"), [&](Ref *pSender)
    {
        this->clickChooseItem();
    });
    pChooseItems->setPosition(880, 597);
    _pChooseItem = pChooseItems;
    
    auto pMenuPanel = Menu::create(pSpeedToggleItem, pPauseItemToggleItem, pChooseItems, nullptr);
    addChild(pMenuPanel);
}

void ScoreAndControllerLayer::registerNotifyEvent()
{
    NOTIFY->addObserver(this, callfuncO_selector(ScoreAndControllerLayer::monsterBatchChange), "monsterBatchChange", nullptr);
    NOTIFY->addObserver(this, callfuncO_selector(ScoreAndControllerLayer::moneyChange), "moneyChange", nullptr);
}

void ScoreAndControllerLayer::unRegisterNotifyEvent()
{
    NOTIFY->removeAllObservers(this);
}

void ScoreAndControllerLayer::moneyChange(cocos2d::Ref *pData)
{
    setMoneyNum(*(reinterpret_cast<int*>(pData)));
}

void ScoreAndControllerLayer::monsterBatchChange(cocos2d::Ref *pData)
{
    setMonsterBatchCount(*(reinterpret_cast<int*>(pData)));
}

void ScoreAndControllerLayer::setMoneyNum(const int &rIMoneyNum)
{
    auto tPos = _pMoneyLabel->getPosition();
    _pMoneyLabel->removeFromParent();
    _iMoney += rIMoneyNum;
    _pMoneyLabel = NumSprite::createNum(StringUtils::format("%d", _iMoney), MONEYNUMIMAGE);
    addChild(_pMoneyLabel);
    _pMoneyLabel->setPosition(tPos);
}

void ScoreAndControllerLayer::setMonsterBatchCount(const int &rIMonsterBatchIndex)
{
    auto tPos = _pMonsterBatchIndex->getPosition();
    _pMonsterBatchIndex->removeFromParent();
    _pMonsterBatchIndex = NumSprite::createNum(StringUtils::format("%02d", rIMonsterBatchIndex), MONSTERBATCHIMAGE);
    addChild(_pMonsterBatchIndex);
    _pMonsterBatchIndex->setPosition(tPos);
}


void ScoreAndControllerLayer::setPauseFlagIsClose()
{
    _bIsOpenChooceMenu = false;
}

void ScoreAndControllerLayer::onExit()
{
    Layer::onExit();
    unRegisterNotifyEvent();
}

void ScoreAndControllerLayer::clickChooseItem()
{
    if(!_bIsOpenChooceMenu)
    {
        auto pPauseLayer = PauseLayer::create();
        pPauseLayer->setFuncFlagPauseLayerIsClose(CC_CALLBACK_0(ScoreAndControllerLayer::setPauseFlagIsClose, this));
        this->addChild(pPauseLayer, 1);
        _bIsOpenChooceMenu = true;
    }
}






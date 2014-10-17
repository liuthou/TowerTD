//
//  MenusLayer.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-9-20.
//
//

#include "MenusLayer.h"
#include "SoundUtil.h"
#include "PublicSourceDefine.h"


bool MenusLayer::init()
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Layer::init());
        
        createMenuItems();
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void MenusLayer::createMenuItems()
{
    auto pBtnadventureMode = MenuItemSprite::create(
                                                    Sprite::createWithSpriteFrameName("btn_adventure_normal_CN.png"),
                                                    Sprite::createWithSpriteFrameName("btn_adventure_pressed_CN.png"),
                                                    [](Ref *pSender)
                                                    {
                                                        auto enLevelScene = std::make_tuple(en_PageSelectScene, 0);
                                                        NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enLevelScene));
                                                    }
                                                    );
    
    pBtnadventureMode->setPosition(Vec2(180, 100));
    
    auto pBtnBossMode = MenuItemSprite::create(
                                               Sprite::createWithSpriteFrameName("btn_boss_normal_CN.png"),
                                               Sprite::createWithSpriteFrameName("btn_boss_pressed_CN.png"),
                                               [](Ref *pSender)
                                               {
                                                   log("boss mode");
                                               }
                                               );
    pBtnBossMode->setPosition(Vec2(pBtnadventureMode->getPositionX() + 300, 100));
    
    if(true)
    {
        auto pLock = Sprite::createWithSpriteFrameName("locked.png");
        pLock->setPosition(pBtnBossMode->getPositionX() + pBtnBossMode->getContentSize().width / 2 - 20, pBtnBossMode->getPositionY() - 20);
        addChild(pLock, 1);
    }
    

    
    auto pBtnNestMode = MenuItemSprite::create(
                                               Sprite::createWithSpriteFrameName("btn_nest_normal_CN.png"),
                                               Sprite::createWithSpriteFrameName("btn_nest_pressed_CN.png"),
                                               [](Ref *pSender)
                                               {
                                                   log("nest mode");
                                               }
                                               );
    
    pBtnNestMode->setPosition(Vec2(pBtnBossMode->getPositionX() + 300, 100));
    if(true)
    {
        auto pLock = Sprite::createWithSpriteFrameName("locked.png");
        pLock->setPosition(pBtnNestMode->getPositionX() + pBtnNestMode->getContentSize().width / 2 - 20, pBtnNestMode->getPositionY() - 20);
        addChild(pLock, 1);
    }
    
    auto pBtnSetting = MenuItemSprite::create(
                                              Sprite::createWithSpriteFrameName("btn_setting_normal.png"),
                                              Sprite::createWithSpriteFrameName("btn_setting_pressed.png"),
                                              [](Ref *pSender)
                                              {
                                                  auto enGameSettingScene = std::make_tuple(en_GameSettingScene, 0);
                                                  NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enGameSettingScene));
                                              }
                                              );
    pBtnSetting->setPosition(Vec2(200, 220));
    
    auto pBtnHelp = MenuItemSprite::create(
                                           Sprite::createWithSpriteFrameName("btn_help_normal.png"),
                                           Sprite::createWithSpriteFrameName("btn_help_pressed.png"),
                                           [](Ref *pSender)
                                           {
                                               auto tEnGameHelpSceneType = std::make_tuple(en_GameHelpScene, 0);
                                               NOTIFY->postNotification("changeScene", reinterpret_cast<Ref *>(&tEnGameHelpSceneType));
                                           });
    pBtnHelp->setPosition(Vec2(750, 220));
    
    auto pMenu = Menu::create(pBtnadventureMode, pBtnBossMode, pBtnNestMode, pBtnSetting, pBtnHelp, nullptr);
    pMenu->setPosition(Vec2::ZERO);
    addChild(pMenu);

}
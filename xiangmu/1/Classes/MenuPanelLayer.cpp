//
//  MenuPanelLayer.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-9-19.
//
//

#include "MenuPanelLayer.h"
#include "SoundUtil.h"
#include "PublicSourceDefine.h"

bool MenuPanelLayer::init()
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Layer::init());
        
        createItemPanel();
    
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void MenuPanelLayer::setPageTurnFunc(const std::function<void (const bool &)> &rFuncPageTurn)
{
    _funcPageTurn = rFuncPageTurn;
}

void MenuPanelLayer::createItemPanel()
{
    auto pBtnHome = MenuItemSprite::create(Sprite::createWithSpriteFrameName("theme_home_normal.png"), Sprite::createWithSpriteFrameName("theme_home_pressed.png"), [](Ref *pSender)
                                           {
                                               auto enWelcomeScene = std::make_tuple(en_WelcomeScene, -1);
                                               NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enWelcomeScene));
                                           });
    pBtnHome->setPosition(Vec2(30, 615));
    
    auto pBtnHelp = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ss_help_normal.png"), Sprite::createWithSpriteFrameName("ss_help_pressed.png"), [](Ref *pSender)
                                           {
                                               auto tEnHelpScene = std::make_tuple(en_GameHelpScene, 0);
                                               NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&tEnHelpScene));
                                           });
    pBtnHelp->setPosition(Vec2(930, 615));
    
    auto pBtnLeft = MenuItemSprite::create(Sprite::createWithSpriteFrameName("theme_pointleft_normal.png"), Sprite::createWithSpriteFrameName("theme_pointleft_pressed.png"), [this](Ref *pSender)
                                           {
                                               _funcPageTurn(true);
                                           });
    pBtnLeft->setPosition(Vec2(80, 320));
    
    auto pBtnRight = MenuItemSprite::create(Sprite::createWithSpriteFrameName("theme_pointright_normal.png"), Sprite::createWithSpriteFrameName("theme_pointright_pressed.png"), [this](Ref *pSender)
                                            {
                                                _funcPageTurn(false);
                                            });
    pBtnRight->setPosition(Vec2(880, 320));
    
    auto pMenu = Menu::create(pBtnHome, pBtnHelp, pBtnLeft, pBtnRight, nullptr);
    addChild(pMenu, 16);

}



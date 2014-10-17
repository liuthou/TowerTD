//
//  TopPanelLayer.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-9-21.
//
//

#include "TopPanelLayer.h"
#include "OptionLayer.h"
#include "DesignLayer.h"
#include "DataCollectLayer.h"
#include "SoundUtil.h"
#include "PublicSourceDefine.h"

TopPanelLayer::~TopPanelLayer()
{
    CC_SAFE_RELEASE_NULL(_pLayerMultiplex);
}

bool TopPanelLayer::init()
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Layer::init());
        
        createMultiplexLayer();
        
        createMenuPanel();
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void TopPanelLayer::createMultiplexLayer()
{
    _pLayerMultiplex = LayerMultiplex::create(OptionLayer::create(), DataCollectLayer::create(), DesignLayer::create(), nullptr);
    _pLayerMultiplex->retain();
    _pLayerMultiplex->setPosition(VisibleRect::center());
    addChild(_pLayerMultiplex);
}

void TopPanelLayer::createMenuPanel()
{
    auto pHomeMenuItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("setting_home_normal.png"), Sprite::createWithSpriteFrameName("setting_home_pressed.png"), [](Ref *pSender)
                                                {
                                                    auto enWelcomeScene = std::make_tuple(en_WelcomeScene, 0);
                                                    NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enWelcomeScene));
                                                });
    pHomeMenuItem->setPosition(pHomeMenuItem->getContentSize().width / 2, 640 - pHomeMenuItem->getContentSize().height / 2 + 5);
    
    auto pOptionMenuItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("options_normal_CN.png"), Sprite::createWithSpriteFrameName( "options_selected_CN.png"), [&](Ref *pSender)
    {
        _pLayerMultiplex->switchTo(0);
    });
    pOptionMenuItem->setPosition(279, 593);
    
    auto pStatisticsMenuItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("statistics_normal_CN.png"), Sprite::createWithSpriteFrameName("statistics_selected_CN.png"), [&](Ref *pSender)
    {
        _pLayerMultiplex->switchTo(1);
    });
    pStatisticsMenuItem->setPosition(479, 593);
    
    auto pCreditsMenuItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("credits_normal_CN.png"), Sprite::createWithSpriteFrameName("credits_selected_CN.png"), [&](Ref *pSender)
    {
        _pLayerMultiplex->switchTo(2);
    });
    pCreditsMenuItem->setPosition(679, 593);
    
    auto pMenu = Menu::create(pHomeMenuItem, pOptionMenuItem, pStatisticsMenuItem, pCreditsMenuItem, nullptr);
    addChild(pMenu);
}
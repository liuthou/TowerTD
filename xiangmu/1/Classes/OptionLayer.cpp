//
//  OptionLayer.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#include "OptionLayer.h"
#include "SoundUtil.h"

bool OptionLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Layer::init());
        
        loadSource();
        
        bRet = true;
    }
    while (0);
    return bRet;
}

void OptionLayer::loadSource()
{
    
    auto pSoundUtil = SoundUtil::getInstance();
    bool bIsBackGroundSound = pSoundUtil->getIsBackGroundSound();
    bool bIsEffectSound = pSoundUtil->getIsEffectSound();
    
    auto pBg = Sprite::createWithSpriteFrameName("setting_bg.png");
    addChild(pBg);
    
    auto pTitle = Sprite::createWithSpriteFrameName("setting_bg_CN.png");
    addChild(pTitle);
    
    
    
    auto pEffectSoundBtnOn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("soundfx_on_CN.png"), Sprite::createWithSpriteFrameName("soundfx_on_CN.png"));
    auto pEffectSoundBtnOff = MenuItemSprite::create(Sprite::createWithSpriteFrameName("soundfx_off_CN.png"), Sprite::createWithSpriteFrameName("soundfx_off_CN.png"));
    auto pEffectSoundToggle = MenuItemToggle::createWithCallback(
                                                                [pSoundUtil](Ref *pSender)
                                                                {
                                                                    pSoundUtil->setIsEffectSound(!pSoundUtil->getIsEffectSound());
                                                                },
                                                                 bIsEffectSound ? pEffectSoundBtnOn : pEffectSoundBtnOff,
                                                                 bIsEffectSound ? pEffectSoundBtnOff : pEffectSoundBtnOn,
                                                                 nullptr);
    pEffectSoundToggle->setPosition(Vec2(-100, 70));
    
    auto pBackGroundSoundOn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("bgmusic_on_CN.png"), Sprite::createWithSpriteFrameName("bgmusic_on_CN.png"));
    auto pBackGroundSoundOff = MenuItemSprite::create(Sprite::createWithSpriteFrameName("bgmusic_off_CN.png"), Sprite::createWithSpriteFrameName("bgmusic_off_CN.png"));
    auto pBackGroundSoundToggle = MenuItemToggle::createWithCallback(
                                                                     [pSoundUtil](Ref *pSender)
                                                                     {
                                                                         pSoundUtil->setIsBackGroundSound(!pSoundUtil->getIsBackGroundSound());
                                                                     },
                                                                     bIsBackGroundSound ? pBackGroundSoundOn : pBackGroundSoundOff,
                                                                     bIsBackGroundSound ? pBackGroundSoundOff : pBackGroundSoundOn,
                                                                     nullptr);
    pBackGroundSoundToggle->setPosition(Vec2(100, 70));
    auto pMenu = Menu::create(pBackGroundSoundToggle, pEffectSoundToggle, NULL);
    addChild(pMenu);
}



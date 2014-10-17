//
//  SoundUtil.cpp
//  newCardDefence
//
//  Created by Yan on 14-8-29.
//
//

#include "SoundUtil.h"
#include "SimpleAudioEngine.h"

SoundUtil *SoundUtil::_gInstance;

void SoundUtil::playBackgroundSound(const std::string &rSBgSound)
{
    if (!_bIsBackGroundSound) return;
    
    if(rSBgSound == BACKGROUNDSOUND && _bIsSoundMainBackGroundMusic) return;
    else
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(rSBgSound.c_str(), true);
        if(rSBgSound == BACKGROUNDSOUND) _bIsSoundMainBackGroundMusic = true;
        else _bIsSoundMainBackGroundMusic = false;
    }

}

void SoundUtil::playEffect(const std::string &rSEffectSound)
{
    if(!_bIsEffectSound) return;
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(rSEffectSound.c_str());
}

void SoundUtil::setIsBackGroundSound(const bool &rIsSound)
{
    _bIsBackGroundSound = rIsSound;
    _bIsSoundMainBackGroundMusic = !rIsSound;
    _bIsBackGroundSound ? playBackgroundSound(BACKGROUNDSOUND) : stopBackGroundSound();
}

void SoundUtil::stopBackGroundSound()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

SoundUtil::SoundUtil():_bIsEffectSound(true)
{

}

SoundUtil::~SoundUtil()
{

}



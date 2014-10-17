#include "AudioUtil.h"

AudioUtil * AudioUtil::instance;
AudioUtil * AudioUtil::getInstance()
{
	if (!instance)
	{
		instance = new AudioUtil();
		instance->autorelease();
		instance->retain();
	}
	return instance;
}

//destroy instance
void AudioUtil::destroyInstance()
{
	CC_SAFE_RELEASE_NULL(instance);
}


void AudioUtil::playBackgroundSound(const char * backGroundName)
{  
	if (!isBackGroundPlay)
	{
		return;
	}
	this->backGroundName = backGroundName;
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(backGroundName,true);
}

void AudioUtil::playEffect(const char * effectName)
{
	if (!isEffectPlay)
	{
		return;
	}
	this->effectName = effectName;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(effectName,false);
}

void AudioUtil::setIsBackGround(const bool &isPlay)
{
	isBackGroundPlay = isPlay;
	isBackGroundPlay ? playBackgroundSound(backGroundName.c_str()):stopBackGroundPlay();
}

void AudioUtil::setIsEffectPlay(const bool &isPlay)
{
	isEffectPlay = isPlay;
	isEffectPlay ? playEffect(effectName.c_str()):stopEffectPlay();
}
bool AudioUtil::getIsEffectPlay()
{
	return isEffectPlay;
}
void AudioUtil::stopEffectPlay()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}


bool AudioUtil::getIsBackGround()
{
	return isBackGroundPlay;
}

void AudioUtil::stopBackGroundPlay()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

AudioUtil::AudioUtil():isEffectPlay(true),isBackGroundPlay(true)
{
	
}


AudioUtil::~AudioUtil()
{

}
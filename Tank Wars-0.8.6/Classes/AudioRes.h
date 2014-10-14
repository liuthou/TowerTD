#ifndef __AUDIORES_H
#define __AUDIORES_H
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
void AudioInit()
{
	SimpleAudioEngine::getInstance()->preloadEffect("bullet.aif");
	SimpleAudioEngine::getInstance()->preloadEffect("02 start.aif");
	SimpleAudioEngine::getInstance()->preloadEffect("gameover.aif");
	SimpleAudioEngine::getInstance()->preloadEffect("move.aif");
	SimpleAudioEngine::getInstance()->preloadEffect("tankbomb.aif");
	SimpleAudioEngine::getInstance()->preloadEffect("addlife.aif");
}
#endif // !__AUDIORES_H

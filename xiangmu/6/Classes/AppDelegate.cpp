#include "AppDelegate.h"
#include "WelComeGameScene.h"
#include "PlayGameScene.h"
#include "SelectGameScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;


AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::loadAudio()
{
    auto audioInstance = SimpleAudioEngine::getInstance();
	//start screen backGround music
	audioInstance->preloadBackgroundMusic("StartBackGround.mp3");
	//game screen backGround music
	audioInstance->preloadBackgroundMusic("GameBackGround.wav");
	//stone bomb
	audioInstance->preloadEffect("bomb.mp3");
	//upthrust
	audioInstance->preloadEffect("upthrust1.mp3");
	audioInstance->preloadEffect("upthrust2.mp3");
	audioInstance->preloadEffect("upthrust3.mp3");
	audioInstance->preloadEffect("upthrust4.mp3");
	audioInstance->preloadEffect("upthrust5.mp3");
	//ice
	audioInstance->preloadEffect("ice.mp3");
	//monster
	audioInstance->preloadEffect("monster.mp3");
	/**
	 *  涓昏鐧诲鐨勫０闊?	 */
	audioInstance->preloadEffect("knockWall.mp3");
    
	//Diamond
	//audioInstance->preloadEffect("Diamond.mp3");
	//eatGold
	audioInstance->preloadEffect("eatGold.mp3");
	//gold
	audioInstance->preloadEffect("gold.mp3");
	//Jewel
	audioInstance->preloadEffect("Jewel.mp3");
	//role die
	audioInstance->preloadEffect("die.mp3");
	//quitTheGame
	audioInstance->preloadEffect("quitTheGame.mp3");
	//upspring
	audioInstance->preloadEffect("upspring.mp3");
	//rotatePop_up
	audioInstance->preloadEffect("rotatePop_up.mp3");
	//balloon
	audioInstance->preloadEffect("balloon.mp3");
    audioInstance->preloadEffect("shit.wav");
    audioInstance->preloadEffect("wood.wav");
    audioInstance->preloadEffect("dou.wav");
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

	//more screen adaptation ,design size 640 * 960
	glview->setDesignResolutionSize(640,960,ResolutionPolicy::EXACT_FIT);
    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
	srand(time(0));
    // create a scene. it's an autorelease object
    auto scene = WelComeGameScene::createScene();

    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

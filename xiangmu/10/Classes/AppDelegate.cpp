#include "AppDelegate.h"
#include "AssetManager.h"
#include "WelcomeScene.h"
#include "AppMacro.h"

AppDelegate::AppDelegate() {
	srand(time(0));
}

AppDelegate::~AppDelegate() {

}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
		director->setOpenGLView(glview);
		
    }

	glview->setDesignResolutionSize(SCREEN_SIZE.width, SCREEN_SIZE.height, ResolutionPolicy::EXACT_FIT);
	glview->setFrameSize(SCREEN_SIZE.width, SCREEN_SIZE.height);

    director->setAnimationInterval(1.0 / 60);
	AssetManager::getInstance();
	Scene *scene = WelcomeScene::create();
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}


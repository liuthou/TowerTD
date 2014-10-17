#include "AppDelegate.h"
#include "GameScene.h"
#include "StartScene.h"
#include "StartScene.h"


USING_NS_CC;
AppDelegate::AppDelegate() {
}
AppDelegate::~AppDelegate() 
{
}
bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
    glview->setDesignResolutionSize(960,640,ResolutionPolicy::EXACT_FIT);
    director->setAnimationInterval(1.0 / 60);

    auto scene = StartScene::create();

    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

}

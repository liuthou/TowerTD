#include "AppDelegate.h"
#include "GameScene.h"
#include "LoadingScene.h"
#include "GameData.h"
#include "ShowLayer.h"
#include "SuspendLayer.h"
#include "GameOverLayer.h"
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
	//多屏幕适配，设计尺寸960*640
	glview->setDesignResolutionSize(960,640,ResolutionPolicy::EXACT_FIT);
    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
	//随机种子
	srand(time(0));
    // create a scene. it's an autorelease object
    auto scene = LoadingScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
	//CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	RenderTexture * renderTexture = RenderTexture::create(VISIBLE_SIZE.width, VISIBLE_SIZE.height);
	renderTexture->retain();
	auto m_scene = Director::getInstance()->getRunningScene();
	if (m_scene->getName() == "game_scene")
	{
		auto showLayer = dynamic_cast<ShowLayer *>(m_scene->getChildByName("showLayer"));
		auto gameOverLayer = showLayer->getM_gameOverLayer();
		auto pauseLayer = showLayer->getM_suLayer();
		if (pauseLayer == nullptr && gameOverLayer == nullptr)
		{
			renderTexture->begin();
			m_scene->visit();
			renderTexture->end();
			//停止重力感应
			Device::setAccelerometerEnabled(false);
			pauseLayer = SuspendLayer::create();
			showLayer->setM_suLayer(pauseLayer);
			showLayer->addChild(pauseLayer);
			Director::getInstance()->pause();
		}
	}
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
     //CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

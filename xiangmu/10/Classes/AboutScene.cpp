#include "AboutScene.h"

Scene *AboutScene::createScene() {
    auto scene = Scene::create();
    scene->addChild(AboutScene::create());
    return scene;
}

bool AboutScene::init() {
    if (!Layer::init())
    {
        return false;
    }
    
    auto rootUI = GUIReader::getInstance()->widgetFromJsonFile(ABOUTUI_JSON);
    auto backBtn = (Button *) rootUI->getChildByName(RETURNBUT);
    backBtn->addTouchEventListener([](Ref *sender, ui::Widget::TouchEventType type){
        if (type == Widget::TouchEventType::BEGAN)	{
            SimpleAudioEngine::getInstance()->playEffect(CLIK_MUSIC);
        }
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto audio = SimpleAudioEngine::getInstance();
            if (audio->isBackgroundMusicPlaying()) {
                audio->pauseBackgroundMusic();
            }
            Director::getInstance()->popScene();
        }
    });
    this->addChild(rootUI);
    
    return true;
}
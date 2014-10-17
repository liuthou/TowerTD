#include "WelcomeScene.h"
#include "MainScene.h"
#include "AssetManager.h"
#include "AboutScene.h"

bool WelcomeScene::init(){
    if (!Scene::init())
    {
        return false;
    }
    initBg();
    
    return true;
}

void WelcomeScene::goStart(Ref *sender){
    auto scene = MainScene::create();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, scene));
}

void WelcomeScene::initBg() {
    m_sp = Sprite::create(BG_PATH);
    m_sp->setPosition(VSIZE/2);
    m_selector = Sprite::create("selector1.png");
    m_selector->setPosition(Vec2(VSIZE.width/2, VSIZE.height * 0.1));
    m_selector->setScale(0.8);
    this->addChild(m_sp);
    this->addChild(m_selector);
    Widget *uiLayer = GUIReader::getInstance()->widgetFromJsonFile("GameStartBG_1/GameStartBG_1.json");
    auto pageView = (PageView *)uiLayer->getChildByName("PV");
    
    // start button
    auto page4 = pageView->getPage(3);
    
    auto startBtn = (Button *)page4->getChildByName("startButton");
    startBtn->addTouchEventListener([=](Ref *s, Widget::TouchEventType t){
        if (t == Widget::TouchEventType::BEGAN)	{
            SimpleAudioEngine::getInstance()->playEffect(CLIK_MUSIC);
        }
        if (t == Widget::TouchEventType::ENDED) {
            goStart(nullptr);
        }
    });
    
    auto aboutBtn = (Button *)page4->getChildByName("aboutButton");
    aboutBtn->addTouchEventListener([](Ref *sender, ui::Widget::TouchEventType type){
        if (type == Widget::TouchEventType::BEGAN)	{
            SimpleAudioEngine::getInstance()->playEffect(CLIK_MUSIC);
        }
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto scene = TransitionSlideInR::create(0.8f, AboutScene::createScene());
            Director::getInstance()->pushScene(scene);
        }
    });
    
    pageView->addEventListener([=](Ref *sender, PageView::EventType type){
        ssize_t page1 = 0;
        ssize_t page2 = 1;
        ssize_t page3 = 2;
        if(pageView->getCurPageIndex() ==page1 ){
            m_selector->setTexture("selector1.png");
        }
        else if (pageView->getCurPageIndex() == page2)
        {
            m_selector->setTexture("selector2.png");
        }else if(pageView->getCurPageIndex() == page3)
        {
            m_selector->setTexture("selector3.png");
        }
    });
    this->addChild(uiLayer);
}

void WelcomeScene::onEnter() {
    Scene::onEnter();
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(COPTER_MUSIC);
    SimpleAudioEngine::getInstance()->preloadEffect(CLIK_MUSIC);
    SimpleAudioEngine::getInstance()->preloadEffect(GETBOMB_MUSIC);
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
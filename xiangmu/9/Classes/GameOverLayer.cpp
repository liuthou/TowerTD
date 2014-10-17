#include "GameOverLayer.h"
#include "StartScene.h"
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;

bool GameOverLayer::init(){
	if (!Layer::init()){
		return false;
	}
	auto vSize = Director::getInstance()->getVisibleSize();
	Widget *uiLayer = GUIReader::getInstance()->widgetFromJsonFile("GameOver_1.json");
	uiLayer->setPosition(Vec2(0, vSize.height));
	auto move = MoveBy::create(0.8, Vec2(0, -vSize.height));
	auto jump = JumpBy::create(0.4, Vec2(0, 0), vSize.height / 16, 2);
	auto layerRun = Sequence::create(move, jump, NULL);
	this->addChild(uiLayer);
	//’Ω∂∑ §¿˚Õº∆¨
	auto imageWin = uiLayer->getChildByName("Image_4");
	auto bink = Blink::create(40, 50);
	this->runAction(layerRun);
	imageWin->runAction(bink);
	//∑µªÿ∞¥≈•
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();//停止播放
	SimpleAudioEngine::getInstance()->playEffect("Gameover.mp3");
    
	auto buttonBack = (Button*)uiLayer->getChildByName("Button_2");
	buttonBack->addTouchEventListener([=](Ref * sender, Widget::TouchEventType touch)
	{
		if (touch == Widget::TouchEventType::ENDED)
		{
            SimpleAudioEngine::getInstance()->unloadEffect("Gameover.mp3");
			auto move2 = MoveBy::create(0.1, Vec2(0, -vSize.height / 16));
			auto move3 = MoveBy::create(0.7, Vec2(0, vSize.height + vSize.height / 16));
			this->runAction(Sequence::create(move2, move3, NULL));
			auto scene = StartScene::createScene();
			auto aniscene = TransitionFade::create(4, scene, Color3B::RED);
			Director::getInstance()->replaceScene(aniscene);
		}
	});
	return true;
}
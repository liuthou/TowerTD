#include "StartGame.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "HelpScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace cocostudio;
using namespace ui;
Scene * StartGame::createScene(){
	Scene * scene = Scene::create();
	StartGame * st = StartGame::create();
	scene->addChild(st);
	return scene;
}
bool StartGame::init(){
	if (!Layer::init())
	{
		return false;
	}
	auto audioInstance = SimpleAudioEngine::getInstance();
	audioInstance->preloadBackgroundMusic("backGroundMusic.wma");
	audioInstance->preloadEffect("bombMusic.wma");
	audioInstance->preloadEffect("overMusic.mp3");
	audioInstance->preloadEffect("button.mp3");
	audioInstance->preloadEffect("enemyHurtMusic.wav");
	audioInstance->preloadEffect("addToolMusic.wav");
	audioInstance->preloadEffect("enemyDieMusic.wav");
	return true;
};
void StartGame::onEnter(){
	Layer::onEnter();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("backGroundMusic.wma");
	Widget * uiLayer = GUIReader::getInstance()->widgetFromJsonFile("GameSTG_1/GameSTG_1.json");
	uiLayer->setScale(2);
	this->addChild(uiLayer);

	auto image = (ImageView *)uiLayer->getChildByName("Image_2");
	auto btn = (Button *)image->getChildByName("Button_57");
	btn->addTouchEventListener([=](Ref * sender,Widget::TouchEventType f){
		if (f == Widget::TouchEventType::ENDED)
		{
			SimpleAudioEngine::getInstance()->playEffect("button.mp3");
			GameScene *scene = GameScene::create();
			Director::getInstance()->replaceScene(scene);
		}
	});

	auto btn1 = (Button *)image->getChildByName("Button_58");
	btn1->addTouchEventListener([=](Ref * sender,Widget::TouchEventType f){

	});

	auto btn2 = (Button *)image->getChildByName("Button_59");
	btn2->addTouchEventListener([=](Ref * sender,Widget::TouchEventType f){

	});

	auto btn3 = (Button *)image->getChildByName("Button_60");
	btn3->addTouchEventListener([=](Ref * sender,Widget::TouchEventType f){
		if (f == Widget::TouchEventType::ENDED)
		{
			SimpleAudioEngine::getInstance()->playEffect("button.mp3");
			auto scene = HelpScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	});
}
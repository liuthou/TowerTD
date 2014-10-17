#include "GameOverLayer.h"
#include "cocos-ext.h"
using namespace extension;
#include <ui/CocosGUI.h>
#include "GameScene.h"
#include "ScoreLayer.h"
#include "StartGame.h"
#include "Tools.h"
#include "Enemys.h"
#include "EnemyBullets.h"
#include "HeroesBullets.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
bool GameOverLayer::init() {
	if (!Layer::init())
	{
		return false;
	}
	auto vSize = Director::getInstance()->getVisibleSize();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	SimpleAudioEngine::getInstance()->playEffect("overMusic.mp3");
	return true;
}

/*Scene *GameOverLayer::createScene() {
	auto scene = Scene::create();
	auto layer = GameOverLayer::create();
	scene->addChild(layer);
	return scene;
}*/

void GameOverLayer::onEnter() {
	Layer::onEnter();
	//addButton();
	/*Scale9Sprite * s = Scale9Sprite::create(Rect(20, 20, 9, 104), "GameOver.png");
	s->setContentSize(Size(vSize.width, vSize.height));
	s->setPosition(this->getContentSize() / 2);*/
	auto s = Sprite::create("GameOver.png");
	s->setAnchorPoint(Vec2(0, 0));
	
	auto label = addScore();
	label->setPosition(s->getContentSize().width/2,s->getContentSize().height/2 + label->getContentSize().height);
	s->addChild(label);
	this->addChild(s);
	addTouch();
}

void GameOverLayer::addTouch() {
	
	auto dis = Director::getInstance()->getEventDispatcher();
	auto listen = EventListenerTouchOneByOne::create();
	listen->onTouchBegan = [=](Touch *t, Event *e){
		auto center = __NotificationCenter::getInstance();
		center->postNotification("BossDie", this);
		return true;
	};
	listen->onTouchEnded = [=](Touch *t, Event *e){
		auto scene = StartGame::createScene();
		Director::getInstance()->replaceScene(scene);
		Director::getInstance()->resume();
		Tools::getInstance()->reset();
		Enemys::getInstance()->reset();
		EnemyBullets::getInstance()->reset();
		HeroesBullets::getInstance()->reset();
	};
	dis->addEventListenerWithSceneGraphPriority(listen, this);
}

Label* GameOverLayer::addScore() {
	GameScene *scene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	ScoreLayer *layer = dynamic_cast<ScoreLayer *>(scene->getScoreLayer());
	int score = layer->getnowScore();
	auto str = StringUtils::format("%d",score);
	auto scoreLabel = Label::createWithSystemFont(str, "Arial", 80);
	scoreLabel->setPosition(vSize.width/2-50,vSize.height/2-50);
	return scoreLabel;
}
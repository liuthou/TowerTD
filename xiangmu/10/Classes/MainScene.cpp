#include "MainScene.h"
#include "BaseAirObject.h"
#include "GameLayer.h"
#include "Enemy.h"
#include "ControlLayer.h"
#include "Prop.h"
#include "ScoreLayer.h"
#include "MainPlane.h"
using namespace CocosDenshion;

bool MainScene::init() {
	if (!Scene::initWithPhysics()) 
	{
			return false;
	}
	initLayers();
	registerCollisionHandlers();
    
    this->setonEnterTransitionDidFinishCallback([](){
        SimpleAudioEngine::getInstance()->playBackgroundMusic(COPTER_MUSIC, true);
    });
    
	return true;
}

void MainScene::initLayers() {
	m_scoreLayer = ScoreLayer::create();
	m_scoreLayer->setLocalZOrder(LayerZorders::SCORE_LAYER);
	m_scoreLayer->setName(SCORELAYERNAME);

	m_controlLayer = ControlLayer::create();
	m_controlLayer->setLocalZOrder(LayerZorders::CONTROL_LAYER);

	m_gameLayer = GameLayer::create();
	m_gameLayer->setLocalZOrder(LayerZorders::GAME_LAYER);

	this->addChild(m_scoreLayer);
	this->addChild(m_controlLayer);
	this->addChild(m_gameLayer);
}

void MainScene::registerCollisionHandlers(){
	auto contactListen = EventListenerPhysicsContact::create();

	contactListen->onContactBegin = [=](PhysicsContact & contact)->bool{
		auto nodeA = contact.getShapeA()->getBody()->getNode();
		auto nodeB = contact.getShapeB()->getBody()->getNode();
		if (nodeA == NULL || nodeB == NULL)
		{
			return false;
		}

		auto tagA = nodeA->getTag();
		auto tagB = nodeB->getTag();

		if (tagA == PLAYER_TAG) {
			auto mainplane = (MainPlane *)nodeA;
			if (tagB == ENEMY_TAG) {
				auto enemy = (Enemy *)nodeB;
				enemy->effectWhileCollision(m_scoreLayer);
				return false;
			} else {
				auto prop = (Prop *)nodeB;
				prop->effectWhileCollision(mainplane);
			}
		} else {
			auto mainplane = (MainPlane *)nodeB;
			if (tagA == ENEMY_TAG) {
				auto enemy = (Enemy *)nodeA;
				enemy->effectWhileCollision(m_scoreLayer);
				return false;
			} else {
				auto prop = (Prop *)nodeA;
				prop->effectWhileCollision(mainplane);
			}
		}

		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListen, this);
}

void MainScene::start() {
	m_controlLayer->start();
	m_gameLayer->start();
	m_scoreLayer->start();
}

void MainScene::onEnter(){
	Scene::onEnter();
	this->start();
}
#include "GameScene.h"
#include "ControlLayer.h"
#include "Edge.h"
#include "LogicLayer.h"
#include "EnemyAILayer.h"
#include "AnimateLayer.h"
#include "BossTwo.h"
#include "ScoreLayer.h"
#include "ui/CocosGUI.h"
#include "StartScene.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace ui;
using namespace cocostudio;


void GameScene::onEnter(){
	Scene::onEnter();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("DragonNest.mp3",true);
}
bool GameScene::init(){
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	
	SimpleAudioEngine::getInstance()->rewindBackgroundMusic();
	

	//英雄层
	HeroLayer *herolayer = HeroLayer::create();
	herolayer->setName("herolayer");
	this->addChild(herolayer,3);

	//显示边框,注释了就不显示了
	//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//负数为添加向下的加速度
	this->getPhysicsWorld()->setGravity(Vec2(0,-1100));



	//可视区域大小
	Size visSize = Director::getInstance()->getVisibleSize();

	//背景图片
	Sprite *bg = Sprite::create("bg19a.jpg");
	bg->setScale(2);
	bg->setPosition(Vec2(visSize.width/2,visSize.height/2));
	this->addChild(bg);



	//创建Edge
	Edge *edge = Edge::create();
	//设置边界为整个可是区域
	edge->setPosition(visSize.width/2,visSize.height/2);
	//设置可以参与碰撞
	//edge->getPhysicsBody()->setContactTestBitmask(1);
	//添加到 层上面
	this->addChild(edge);

	//控制层
	ControlLayer *controller = ControlLayer::create();
	controller->setName("controller");
	this->addChild(controller,9);

	//添加 敌人层
	auto enemyLayer = EnemyLayer::create();
	enemyLayer->setName("enemylayer");
	this->addChild(enemyLayer,3);

	//地图
	MapLayer *maplayer = MapLayer::create();
	maplayer->setName("maplayer");
	this->addChild(maplayer,0);


	//逻辑层
	LogicLayer *logic = LogicLayer::create();
	this->addChild(logic);

	//添加动画层
	AnimateLayer * animatelayer = AnimateLayer::create();
	this->addChild(animatelayer);

	//怪物AI层
	auto enemyAILayer = EnemyAILayer::create();
	this->addChild(enemyAILayer);


	//创建一个底面
	auto background = Sprite::create();//就是一个精灵
	background->setTag(2001);
	background->setPhysicsBody(PhysicsBody::createBox(Size(visSize.width,74)));
	background->setTextureRect(Rect(0,0,visSize.width,74));//设置纹理的 宽 高
	background->getPhysicsBody()->setCategoryBitmask(16);
	background->getPhysicsBody()->setCollisionBitmask(31);
	background->getPhysicsBody()->setContactTestBitmask(0);
	background->setPosition(visSize.width/2,5);//设置地板的 位置 
	background->getPhysicsBody()->setDynamic(false);
	background->setOpacity(0);//设置透明度为0
	this->addChild(background);


	//创建积分层
	ScoreLayer *scoreLayer = ScoreLayer::create();
	scoreLayer->setName("scoreLayer");
	this->addChild(scoreLayer,9);

	SkillLayer *skill = SkillLayer::create();
	skill->setName("skilllayer");
	this->addChild(skill,9);

	return true;
}
HeroLayer * GameScene::getHeroLayer(){
	return this->getChildByName<HeroLayer *>("herolayer");
}

EnemyLayer * GameScene::getEnemyLayer(){
	return this->getChildByName<EnemyLayer *>("enemylayer");
}

MapLayer * GameScene::getMapLayer(){
	return this->getChildByName<MapLayer *>("maplayer");
}

ScoreLayer *GameScene::getScoreLayer(){
	return (ScoreLayer *)this->getChildByName("scoreLayer");
}

SkillLayer *GameScene::getSkillLayer(){
	return (SkillLayer *)this->getChildByName("skilllayer");
}
ControlLayer *GameScene::getControlLayer(){
	return this->getChildByName<ControlLayer *>("controller");
}


#include "MainScene.h"
#include "MapLayer.h"
#include "TouchLayer.h"
#include "BackgroundLayer.h"
#include "MonsterAttributeConfType.h"
#include "MonsterAttribute.h"
#include "GameLayer.h"
#include "Enemy.h"
#include "TowerAttributeConfType.h"
#include "TowerAttribute.h"
#include "GameLayer.h"
#include "MonsterManager.h"
#include "ForwardLayer.h"
#include "FileManager.h"
#include "InjuredEffent.h"
#include "BasicAttribute.h"
#include "LoseScene.h"
#include "EntityManager.h"
#include "WinScene.h"
#include "MonsterManagerAttribute.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool MainScene::init(std::string filename,int chapternum){
	if (!Scene::create()){
		return false;
	}
	SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm.mp3",true);
	this->filename = filename;
	this->chapternum = chapternum;
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size size = Director::getInstance()->getVisibleSize();
	//读取关卡文件
	BasicAttribute::setXmlFilename(filename);
	//添加背景层
	backgroundlayer = BackgroundLayer::create();
	this->addChild(backgroundlayer);
	//添加地图层
	maplayer = MapLayer::create();
	maplayer->setTag(100);
	this->addChild(maplayer);
	//添加游戏层
	gamelayer = GameLayer::create();
	this->addChild(gamelayer,10);
	//添加Touch层
	touchlayer = TouchLayer::create();
	touchlayer->setName("touchlayer");
	this->addChild(touchlayer);
	//游戏层
	gameLayer = GameLayer::create();
	gameLayer->setName("wode");
	this->addChild(gameLayer);
	//前景层
	forwardlayer = ForwardLayer::create();
	forwardlayer->setName("progressLayer");
	this->addChild(forwardlayer);
	//受伤效果层
	injuredlayer = InjuredEffect::create();
	injuredlayer->setName("injuredEffect");
	this->addChild(injuredlayer);




	//得到一个怪物管理器
	monstermanager=MonsterManager::create();
	this->addChild(monstermanager);

	//得到一个文件管理器
	filemanager = FileManager::create();

	this->addChild(filemanager);
	this->initLayers();
	return true;
}
void MainScene::initLayers(){
	//设置初始分数
	forwardlayer->setcurSorce(2000);
	//绑定减分函数
	touchlayer->setCutScore(CC_CALLBACK_1(ForwardLayer::cutScore,forwardlayer));
	//绑定加分函数
	monstermanager->setEarnScoreFunc(CC_CALLBACK_1(ForwardLayer::plusScore,forwardlayer));
}
Scene* MainScene::create(std::string filename,int chapternum){
	auto scene = new MainScene();
	if (scene&&scene->init(filename,chapternum))
	{
		scene->autorelease();
		return scene;
	}
	CC_SAFE_DELETE(scene);
	return scene;
}

void MainScene::initGame(){

}
void MainScene::win(){
	//当前关卡通过
	int nowchapternum = UserDefault::getInstance()->getIntegerForKey("passedchapter");
	if (chapternum>nowchapternum)
	{
		UserDefault::getInstance()->setIntegerForKey("passedchapter",chapternum);
	}
	this->changeWinScene();
}

void MainScene::lose(){
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size size = Director::getInstance()->getVisibleSize();
	Vector<Node*> layers = this->getChildren();
	for (auto it = layers.begin();it<layers.end();it++)
	{
		(*it)->ignoreAnchorPointForPosition(false);
		(*it)->setAnchorPoint(Vec2(0.5,0.5));
		(*it)->setPosition(origin.x+size.width/2,origin.y+size.height/2);
		auto mscale = ScaleTo::create(0.3,1,0,0);
		(*it)->runAction(mscale);
	}
	auto maction = Sequence::create(DelayTime::create(0.3),CallFunc::create(CC_CALLBACK_0(MainScene::changeLoseScene,this)),NULL);
	this->runAction(maction);
}
void MainScene::changeLoseScene(){
	///停止音效////////////////////////////////////////////////
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
	auto scene = LoseScene::createScene();
	EntityManager::getInstance()->reset();
	Director::getInstance()->replaceScene(scene);
}
void MainScene::changeWinScene(){
	auto scene = WinScene::create();
	int killnum = EntityManager::getInstance()->getMonsterKilledNum();
	scene->setNumber(killnum);
	EntityManager::getInstance()->reset();
	Director::getInstance()->replaceScene(scene);
}
MapLayer *MainScene::getMapLayer(){
	return dynamic_cast<MapLayer *>(this->getChildByTag(100));
}
Layer *MainScene:: getGameLayer(){
	return this->getChildByName<Layer*>("wode");
}
MainScene::~MainScene(){
	MonsterAttribute::destoryInstance();
	MonsterManagerAttribute::destoryInstance();
	TowerAttribute::destoryInstance();
}
#include "BackgroundLayer.h"
#include "GameMainScene.h"
#include "MonsterLayer.h"
#include "tinyxml2/tinyxml2.h"
using namespace tinyxml2;

BackgroundLayer *BackgroundLayer::create(std::string filename){
	auto layer = new BackgroundLayer();
	if (layer&&layer->init(filename)){
		layer->autorelease();
		return layer;
	}
	else
	{
		CC_SAFE_DELETE(layer);
		return nullptr;
	}
}

bool BackgroundLayer::init(std::string filename)
{
	if (!Layer::init())
	{
		return false;	
	}
	testXML(filename);
	auto centerBackgroundMoveRight = __NotificationCenter::getInstance();
	centerBackgroundMoveRight->addObserver(this,callfuncO_selector(BackgroundLayer::backgroundMoveRight), "backgroundMoveRight",nullptr);
	auto centerBackgroundMoveLeft = __NotificationCenter::getInstance();
	centerBackgroundMoveLeft->addObserver(this,callfuncO_selector(BackgroundLayer::backgroundMoveLeft), "backgroundMoveLeft",nullptr);
	auto centerStopBackgroundMove = __NotificationCenter::getInstance();
	centerStopBackgroundMove->addObserver(this,callfuncO_selector(BackgroundLayer::stopBackgroundMove), "stopBackgroundMove",nullptr);
	return true;
}

void BackgroundLayer::testXML(std::string filename)
{
	auto fileName = FileUtils::getInstance()->fullPathForFilename(filename);
	tinyxml2::XMLDocument xmlDoc;
	xmlDoc.LoadFile(fileName.c_str());
	XMLElement *  root = xmlDoc.RootElement();
	XMLElement *  xmlbg1 = root->FirstChildElement("Background");
    _background = Sprite::create(xmlbg1->FirstChildElement()->GetText());
	_background->setAnchorPoint(Vec2(0,0));
    this->addChild(_background);
}

void BackgroundLayer::backgroundMoveRight(Ref * obj)
{	
	unschedule(schedule_selector(BackgroundLayer::baclgroundMoveLeftUpdate));
	schedule(schedule_selector(BackgroundLayer::baclgroundMoveRightUpdate),0);
}

void BackgroundLayer::baclgroundMoveRightUpdate(float t)
{
	GameMainScene * gameMainScene = dynamic_cast<GameMainScene *>(Director::getInstance()->getRunningScene());
	MonsterLayer * monsterLayer = dynamic_cast<MonsterLayer *>(gameMainScene->getMonsterLayer());
	Size zSize = Director::getInstance()->getVisibleSize();
	if(this->getPositionX() <= -zSize.width * 1.1)
	{
	    auto centerBackgroundMove = __NotificationCenter::getInstance();
	    centerBackgroundMove->postNotification("centerMoveRight");
	}
	else
	{
		this->setPositionX(this->getPositionX() - 3);
		monsterLayer->setPositionX(monsterLayer->getPositionX() - 3);
	}
	
}

void BackgroundLayer::backgroundMoveLeft(Ref * obj)
{
	unschedule(schedule_selector(BackgroundLayer::baclgroundMoveRightUpdate));
	schedule(schedule_selector(BackgroundLayer::baclgroundMoveLeftUpdate),0);
}

void BackgroundLayer::baclgroundMoveLeftUpdate(float t)
{
	GameMainScene * gameMainScene = dynamic_cast<GameMainScene *>(Director::getInstance()->getRunningScene());
	MonsterLayer * monsterLayer = dynamic_cast<MonsterLayer *>(gameMainScene->getMonsterLayer());
	Size zSize = Director::getInstance()->getVisibleSize();
	if(this->getPositionX() > 0)
	{
	    auto centerBackgroundMove = __NotificationCenter::getInstance();
	    centerBackgroundMove->postNotification("centerMoveLeft");
	}
	else
	{   
		this->setPositionX(this->getPositionX() + 5);
		monsterLayer->setPositionX(monsterLayer->getPositionX() + 5);
	}
}

void BackgroundLayer::stopBackgroundMove(Ref * obj)
{
	unschedule(schedule_selector(BackgroundLayer::baclgroundMoveRightUpdate));
	unschedule(schedule_selector(BackgroundLayer::baclgroundMoveLeftUpdate));
}

BackgroundLayer::~BackgroundLayer()
{
    auto centerBackgroundMoveRight = __NotificationCenter::getInstance();
	centerBackgroundMoveRight->removeObserver(this, "backgroundMoveRight");
	auto centerBackgroundMoveLeft = __NotificationCenter::getInstance();
	centerBackgroundMoveLeft->removeObserver(this, "backgroundMoveLeft");
	auto centerStopBackgroundMove = __NotificationCenter::getInstance();
	centerStopBackgroundMove->removeObserver(this, "stopBackgroundMove"); 
}
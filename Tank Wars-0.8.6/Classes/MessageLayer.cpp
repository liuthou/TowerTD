#include "MessageLayer.h"
#include "GameScene.h"
#include "BaseTank.h"
bool MessageLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto sprite = Sprite::createWithSpriteFrameName("en1.png");
	sprite->setPosition(Vec2(825,400));
	sprite->setTag(1);
	this->addChild(sprite);
	auto sp1 = Sprite::createWithSpriteFrameName("flag.png");
	sp1->setPosition(Vec2(850,200));
	this->addChild(sp1);
	//敌军坦克计数
	enemycount=20;
	enemystr = StringUtils::format("x %d",enemycount);
	enemylable = Label::createWithSystemFont(enemystr,"Airal",20);
	score=0;
	enemylable->setPosition(870,400);
	this->addChild(enemylable);
	scorestr = StringUtils::format("score:%d",score);
	scorelable = Label::createWithSystemFont(scorestr,"Airal",20);
	scorelable->setPosition(Vec2(850,500));
	this->addChild(scorelable);
	auto center = __NotificationCenter::getInstance();
	center->addObserver(this,callfuncO_selector(MessageLayer::reciveEnemyDie),"EnemyDie",nullptr);//注册敌军死亡通知 
	return true;
}
void MessageLayer::reciveEnemyDie(Ref * obj)
{  
	auto basetank = (BaseTank *)obj;
	enemycount--;
	if (enemycount<0)
	{
		enemycount = 999;
	}
	//这里添加关卡管理
	enemystr = StringUtils::format("x %d",enemycount);
	enemylable->setString(enemystr);
	score = score+basetank->getscore();
	scorestr = StringUtils::format("score:%d",score);
	scorelable->setString(scorestr);
	//分数改变
}
void MessageLayer::onEnter()
{
	Layer::onEnter();
	auto scene =dynamic_cast<GameScene *> (Director::getInstance()->getRunningScene());
	auto tank = (BaseTank*)scene->getTanklayer()->getChildByName("tank");
	if (tank == nullptr)
	{
		return;
	}//判定Tank是否为空
	auto center = __NotificationCenter::getInstance();
	center->addObserver(this,callfuncO_selector(MessageLayer::reciveTankHurt),"TankHurt",tank);
	tankHP = tank->getHp();
	tankHPstr = StringUtils::format("HP x %d",tankHP);
	tankHPlable = Label::createWithSystemFont(tankHPstr,"Airal",20);
	tankHPlable->setPosition(850,150);
	this->addChild(tankHPlable);

}
void MessageLayer::reciveTankHurt(Ref *obg)
{
	tankHP = ((BaseTank *)(obg))->getHp();
	tankHPstr = StringUtils::format("HPx %d",tankHP);
	tankHPlable->setString(tankHPstr);
}
//消息监听
MessageLayer::~MessageLayer()
{
	auto center = __NotificationCenter::getInstance();
	center->removeAllObservers(this);
}
//卸载消息监听
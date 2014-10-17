#include "BaseTower.h"
#include "GameManager.h"
#include "GameScene.h"
//#include "UpdateLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio;
BaseTower::BaseTower()
:curgold(100)
,maxlevel(4)
,curlevel(0)
,speed(0)
,goldvalue(50)
,soldier(NULL)
,isAttackTime(false)
,ischangeState(false)
,isPreAttackTime(false)
,scope(0)
{}
BaseTower::~BaseTower(){}
bool BaseTower::init()
{
	if(!Sprite::init())
	{
		return false;
	}
	Armature* toweramt = Armature::create("Project Animation");
	toweramt->setName("toweramimature");
	this->addChild(toweramt);
	this->scheduleUpdate();
	this->stopAnm();
	GameManager::getInstance()->towerVector.pushBack(this);
	postuplevel();
	return true;
}
void BaseTower::update(float dt)
{
	checkNearestEnemy(); 
	changeState();
}
void BaseTower::changeState()
{
	if (ischangeState)
	{
		ischangeState=false;
		if (isAttackTime)
		{
			this->schedule(schedule_selector(BaseTower::Attack),speed);
		}else
		{
			this->unschedule(schedule_selector(BaseTower::Attack));
			this->stopAnm();
		}		
	}
}
void BaseTower::setSpeed(float dt)
{
	speed = dt; 
}
void BaseTower::checkNearestEnemy()
{	
	//这里面需要得到GameManager 的敌人数组  根据敌人和塔的位置求距离 和自己设定的距离作比较
	//同时给出满足距离范围内的enemy 然后通过 rotateAndAttack(float dt) 运行不同的动画
    GameManager * instance = GameManager::getInstance();
	auto enemyvector = instance->enemyVector;
    for(int i =0;i<enemyvector.size();i++)
	{
		auto enemy = enemyvector.at(i);
		auto distance = this->getPosition().getDistance(enemy->getPosition());
		if (distance <=scope)
		{
			if(enemy->getLive()!=DIE){
				soldier=enemy;
				isAttackTime=true;
				if (isAttackTime!=isPreAttackTime)
				{
					isPreAttackTime=isAttackTime;
					ischangeState=true;				
				}
				targetpoint=soldier->getPosition();
				return;
			}
			
		}
	 }
	soldier = nullptr;
	isAttackTime=false;
	if (isAttackTime!=isPreAttackTime)
	{
		isPreAttackTime=isAttackTime;
		ischangeState=true;				
	}

}
//发送升级
 void BaseTower::postuplevel()
 {	
	if (curlevel >= maxlevel)
	{
		return;
	}
	auto center =__NotificationCenter::getInstance();
	center->postNotification("update",this);
}
 void BaseTower::uplevel(){
	
     curlevel++;
	 curgold*=1.5;
	 goldvalue=curgold/2;
	 speed*=0.75;
	 scope*=1.25;
	 //塔升级动画
	  if(curlevel>1)
	  {
		  Sprite *sprite = Sprite::createWithSpriteFrameName("up1.png");
		  sprite->setPosition(Vec2(0,0));
		  this->addChild(sprite);
		  log("{%.2f,%.2f}",sprite->getPosition().x,sprite->getPosition().y);
		  animat = Animation::create();
		  auto cach =  SpriteFrameCache::getInstance();
		  for(int i =1;i<7;i++)
		  {
			  fileName = StringUtils::format("up%d.png",i);
			  animat->addSpriteFrame(cach->getSpriteFrameByName(fileName));

		  }
		  animat->setDelayPerUnit(0.1f);
		  animat->setLoops(1);
		  ani = Animate::create(animat);
		  auto cf = CallFunc::create([=](){
			  sprite->removeFromParentAndCleanup(true);
		  });
		   sprite->runAction(Sequence::create(ani,cf,NULL));
	  }
 }
 //删除塔的方法
void BaseTower::removeTower()
{
	GameManager::getInstance()->towerVector.eraseObject(this);
	this->removeFromParentAndCleanup(true);
}

//发送删除
void BaseTower::postDeleteTower()
{  
	auto center =__NotificationCenter::getInstance();
	center->postNotification("remove",this) ; 
}
void BaseTower::runAnimate(std::string name){
	auto toweramt = this->getChildByName<Armature*>("toweramimature");
	 
	toweramt->getAnimation()->play(name);
} 

void BaseTower::pauseAllTowers()
{
	auto toweramt = this->getChildByName<Armature*>("toweramimature");

	toweramt->getAnimation()->pause();
}






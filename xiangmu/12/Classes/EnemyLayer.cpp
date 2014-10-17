#include "EnemyLayer.h"
#include "Enemy.h"
#include "GameManager.h"
#include "GameBasic.h"
#include "platform/apple/CCFileUtilsApple.h"

bool Enemylayer::init(){
	if(!Layer::init()){
		return false;
	}
	enemyGroup = GameManager::getInstance()->enemyGroups;
	roleInfo = FileUtilsApple::getInstance()->getValueMapFromFile("role.npc");
	count = 0;
	round = 0;
	number = 0;
	isContinue = true;
	this->scheduleUpdate();
	return true;
}
void Enemylayer::addEnemyGroup() //add enemy group next wave
{
	__NotificationCenter::getInstance()->postNotification("wavedown",this);
	
	if (round >= enemyGroup.size())
	{  
		log("enemy is over");
		this->unscheduleUpdate();
		return;
	}
   
	float delaytime = enemyGroup[round].at("delytime").asFloat();
    enemyRound = enemyGroup[round].at("enemyround").asValueVector();
	CallFunc *callfunc = CallFunc::create([=](){
		SimpleAudioEngine::getInstance()->playEffect("dengerious.mp3");
		this->addEnemyRound();
	    
	});
	this->runAction(Sequence::create(DelayTime::create(delaytime),callfunc,nullptr));
	round++;
}
void Enemylayer::addEnemyRound() //add enemy 
{
	if (count >= enemyRound.size())
	{   

		count = 0;
		isContinue = true;
		//this->addEnemyGroup();
		return;
	}
	float delaytime = enemyRound[count].asValueMap().at("delytime").asFloat();
	auto enemys = enemyRound[count].asValueMap().at("number").asInt();
	auto enemyType = enemyRound[count].asValueMap().at("type").asString();
	CallFunc *callfunc = CallFunc::create([=](){this->addEnemys(enemyType,enemys,delaytime);});
	this->runAction(Sequence::create(DelayTime::create(delaytime),callfunc,nullptr));
	count++;
	
}
void Enemylayer::addEnemys(std::string enemyType,int enemys,float delaytime) //add enemy numbers the same kind
{   
	if (number >= enemys)
	{
		number = 0;
		this->addEnemyRound();
		return;
	}
	CallFunc *callfunc = CallFunc::create([=](){this->addEnemys(enemyType,enemys,delaytime);});
	this->runAction(Sequence::create(DelayTime::create(delaytime),callfunc,nullptr));
	auto enemyinfo = roleInfo.at(enemyType);
	auto roleName = enemyinfo.asValueMap().at("name").asString();
	auto roleHp = enemyinfo.asValueMap().at("hp").asFloat();
	auto roleSpeed = enemyinfo.asValueMap().at("speed").asFloat();
	auto roleMoney = enemyinfo.asValueMap().at("money").asInt();
	auto enemy = Enemy::create(roleName,roleHp,roleSpeed,roleMoney);
	this->addChild(enemy);
 	log("%.2f,%.2f",enemy->getAnchorPoint().x,enemy->getAnchorPoint().y);
	number++;
}
void Enemylayer::update(float t)
{   
	auto enemySize = GameManager::getInstance()->enemyVector.size(); 
	if (isContinue == true && enemySize <= 0)
	{
		this->addEnemyGroup();
		isContinue = false;
	}
}
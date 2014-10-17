#include "FirstBoss.h"
#include "ShapeBullet.h"
#include "QuadrantBullet.h"
#include "GameScene.h"
#include "EnemyLayer.h"
#include "ShareFunc.h"
#include "EnemyBullets.h"
#include "LinearBullet.h"
#include <tinyxml2/tinyxml2.h>
using namespace tinyxml2;

FirstBoss * FirstBoss::create(int level){
	FirstBoss *pRet = new FirstBoss();
	if (pRet && pRet->initWithSpriteFrameName(level))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
bool FirstBoss::initWithSpriteFrameName(int level){
	xmlCreate_boss();
	this->setEnemySpeed(500 * level);

	this->setHp(2000);

	this->setScore(1500);
	if (!BaseEnemy::initWithSpriteFrameName(myfileName,0,1))
	{
		return false;
	}
	srand(time(0));

	this->level = level;
	int i = CCRANDOM_0_1()*500+100;
	this->setPosition(900,i);
	
	return true;
}
void FirstBoss::xmlCreate_boss(){
	float n = CCRANDOM_0_1();
    n = n < 0.3 ? 1 : n < 0.6 ? 2 : 3;
	std::string str = FileUtils::getInstance()->fullPathForFilename("ThreeBossPit.xml");
	tinyxml2::XMLDocument doc;
	doc.LoadFile(str.c_str());
	tinyxml2::XMLElement * root = doc.RootElement();
	
	str = StringUtils::format("Sprite%d",(int)n);
	tinyxml2::XMLElement * _firstElement = root->FirstChildElement(str.c_str());
	tinyxml2::XMLElement * _in_firstElement = _firstElement->FirstChildElement();
	myfileName = _in_firstElement->GetText();
	tinyxml2::XMLElement * _in_firstElement_number = _firstElement->FirstChildElement("FrameNumber");
	std::string num = _in_firstElement_number->GetText();
	FrameNumber = atoi(num.c_str());
	tinyxml2::XMLElement * _in_firstElement_Die = _firstElement->FirstChildElement("Dieimage");
	myfileName_Die = _in_firstElement_Die->GetText();
	tinyxml2::XMLElement * _in_firstElement_number_die = _firstElement->FirstChildElement("DieFrameNumber");
    num = _in_firstElement_number_die->GetText();
	FrameNumberDie = atoi(num.c_str());

}
void FirstBoss::onEnter(){
	BaseBoss::onEnter();

	auto dieAni = ShareFunc::getAct(myfileName, 1, FrameNumber, 0.2, -1);
	this->runAction(dieAni);
	this->schedule(schedule_selector(FirstBoss::addFire),1,2,0);
	this->schedule(schedule_selector(FirstBoss::addFireStyle),2,-1,3);
	this->schedule(schedule_selector(FirstBoss::SpeicalBullet),20,-1,5);
}
void FirstBoss::addFire(float t){
	GameScene *scenelayer = (GameScene *)Director::getInstance()->getRunningScene();
	auto heroLayer = scenelayer->getHeroLayer();
	auto hero = heroLayer->getChildByName("hero");
	//Boss 3连发子弹速度
	QuadrantBullet *bullet = QuadrantBullet::create(this->getEnemySpeed()/2,this->getPosition(),1000,"EnemyBullet8.png",hero->getPosition(),1);
	EnemyLayer *enemyLayer = (EnemyLayer *)scenelayer->getEnemyLayer();
	enemyLayer->addChild(bullet);
	EnemyBullets::getInstance()->addBullet(bullet);
	this->runAction(MoveBy::create(2,Vec2(-50,-10)));
}
void FirstBoss::addFireStyle(float t){
	int bulletstyle = CCRANDOM_0_1() > 0.8 ?0 : 1;
	if (bulletstyle)
	{
		bulletstyle+=1;
		int number = CCRANDOM_0_1()*4+3;
		this->number = number;
		//Boss 子弹的频率0.5 形状
		this->schedule(schedule_selector(FirstBoss::bulletshape),0.8,number-3,0);
		if (this->getPositionY()<640-this->getContentSize().height/2&&this->getPositionX()<960-this->getContentSize().width/2)
		{
			this->runAction(MoveBy::create(1,Vec2(bulletstyle * 50, bulletstyle * 50)));
		}
		
	}else
	{
		bulletstyle+=1;
		int number = CCRANDOM_0_1()*2+1;
		this->number = number;
		//Boss 子弹的频率0.5 象限
		this->schedule(schedule_selector(FirstBoss::bulletliner),3.0,number-1,0);
		if (this->getPositionX()>320&&this->getPositionY()>this->getContentSize().height/2)
		{
			this->runAction(MoveBy::create(1,Vec2(bulletstyle * -50, bulletstyle * -50)));
		}
	}
	
}
void FirstBoss::bulletshape(float t){
	GameScene *scenelayer = (GameScene *)Director::getInstance()->getRunningScene();
	EnemyLayer *enemy = (EnemyLayer *)scenelayer->getEnemyLayer();
	auto heroLayer = scenelayer->getHeroLayer();
	auto hero = heroLayer->getChildByName("hero");
	log("speed %f",this->getEnemySpeed());
	ShapeBullet * bullet = ShapeBullet::create(this->getEnemySpeed()/400,this->getPosition(),1000,"EnemyBullet7.png",hero->getPosition(),number);
	enemy->addChild(bullet);
	number--;
}
void FirstBoss::bulletliner(float){
	GameScene *scenelayer = (GameScene *)Director::getInstance()->getRunningScene();
	EnemyLayer *enemy = (EnemyLayer *)scenelayer->getEnemyLayer();
	auto heroLayer = scenelayer->getHeroLayer();
	auto hero = heroLayer->getChildByName("hero");
	//BOSS子弹速度1.0
	QuadrantBullet *bullet = QuadrantBullet::create(this->getEnemySpeed()/3,this->getPosition(),1000,"EnemyBullet8.png",hero->getPosition(),1);
	enemy->addChild(bullet);
	EnemyBullets::getInstance()->addBullet(bullet);
}
ActionInterval * FirstBoss::enemyDie(){

	auto dieAni = ShareFunc::getAct(myfileName_Die, 1, FrameNumberDie, 0.2, 1);

	auto center = __NotificationCenter::getInstance();
	center->postNotification("BossDie", this);
	center->postNotification("upLevel", this);
	this->unschedule(schedule_selector(FirstBoss::addFireStyle));


	return dieAni;
}

void FirstBoss::enemyFly(){

}
void FirstBoss::enemyHurt(){
	//受伤动画
	auto sp = Sprite::create();
	sp->setPosition(100, 179);
	sp->setScale(8);
//	this->addChild(sp);
	auto ani = ShareFunc::getAct("EnemyHurt1.png", 1, 6, 0.2, 1);
	auto cf = CallFunc::create([=](){
		sp->removeFromParentAndCleanup(true);
	});
	sp->runAction(Sequence::create(ani, cf, NULL));
}
void FirstBoss::SpeicalBullet(float t){
	GameScene *scenelayer = (GameScene *)Director::getInstance()->getRunningScene();
	EnemyLayer *enemy = (EnemyLayer *)scenelayer->getEnemyLayer();
	auto heroLayer = scenelayer->getHeroLayer();
	auto hero = heroLayer->getChildByName("hero");
	auto cf = CallFunc::create([=](){
		Sprite * s = Sprite::create();
		s->setPosition(Vec2(0,200));
		auto dieAni = ShareFunc::getAct("0.png", 1, 6, 0.2, 1);
		auto cc = CallFunc::create([=](){
			s->removeFromParentAndCleanup(true);
		});
		s->runAction(Sequence::create(dieAni,cc,NULL));
		this->addChild(s);
	});
	auto d_time = DelayTime::create(1.5);
	auto cf_one = CallFunc::create([=](){
		GameScene *scenelayer = (GameScene *)Director::getInstance()->getRunningScene();
		EnemyLayer *enemy = (EnemyLayer *)scenelayer->getEnemyLayer();
		LinearBullet * bullet = LinearBullet::create(100,Vec2(this->getPositionX()-500,this->getPositionY()),500,"0.png",1,1);
		auto d_time = DelayTime::create(3);
		auto dieAni_two = ShareFunc::getAct("6.png",8,15, 0.1, 3);
		auto cf_two = CallFunc::create([=](){
			bullet->removeFromParentAndCleanup(true);
			bullet->setDie(true);
		});
		bullet->runAction(Sequence::create(dieAni_two,cf_two,NULL));
		EnemyBullets::getInstance()->addBullet(bullet);
		enemy->addChild(bullet);
	});
	this->runAction(Sequence::create(MoveTo::create(0.1,Vec2(this->getPositionX(),hero->getPositionY())),cf,d_time,cf_one,NULL));
}

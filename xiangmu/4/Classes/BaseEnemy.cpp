#include "BaseEnemy.h"
#include "Enemys.h"
#include "ToolSkills.h"
#include "ToolBomb.h"
#include "GameScene.h"
#include "QuadrantBullet.h"
#include "EnemyBullets.h"
#include "Tools.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
bool BaseEnemy::initWithSpriteFrameName(std::string fileName, int sb, int level) {

	if (!Sprite::initWithSpriteFrameName(fileName)){
		return false;
	}

	scene = ShareFunc::getGameScene();
	//scene->retain();

    //初始化赋初值
	vSize = Director::getInstance()->getVisibleSize();

	this->isDie = false;

	this->sb = sb;

	switch (level) {
	case 1:
		//等级1 赋初值
		this->bulletCoefficient = 1.0;
		initPro(this->bulletCoefficient);
		break;
	case 2:
		//等级2 赋初值
		this->bulletCoefficient = 1.3;
		initPro(this->bulletCoefficient);
		break;
	case 3:
		//等级3 赋初值
		this->bulletCoefficient = 1.7;
		initPro(this->bulletCoefficient);
	}

	return true;
	
}

void BaseEnemy::onEnter()
{
	Sprite::onEnter();
	enemyFly();
}


//系数初始化属性
void BaseEnemy::initPro(float coefficient){

	this->setEnemySpeed(this->getEnemySpeed() * coefficient);

	this->setHp(this->getHp() * coefficient);

	this->setScore(this->getScore() * (int)coefficient);


}

//死亡后删除该节点
void BaseEnemy::removeEnemyNode(){
	this->setDie(true);
	this->removeFromParentAndCleanup(true);
}

//是否创建道具
void BaseEnemy::isSkillsBomb(int sb){
	ToolSkills* ts = NULL;
	ToolBomb* tb = NULL;
	switch (sb) {
	//创建技能道具
	case 100:
		ts = ToolSkills::create(this->getPosition());
		scene->getEnemyLayer()->addChild(ts);
		Tools::getInstance()->addTools(ts);
		break;
	//创建雷道具
	case 200:
		tb = ToolBomb::create(this->getPosition());
		scene->getEnemyLayer()->addChild(tb);
		Tools::getInstance()->addTools(tb);
		break;
	default:
		
		break;
	}

}

void BaseEnemy::hurt(int attack)
{
	SimpleAudioEngine::getInstance()->playEffect("enemyHurtMusic.wav");
	this->setHp(this->getHp() - (float)attack);
	this->enemyHurt();
	if (this->getHp() <= 0) {
		this->die();
	}
}


void BaseEnemy::die()
{
	SimpleAudioEngine::getInstance()->playEffect("enemyDieMusic.wav");

	this->setDie(true);

	this->stopAllActions();

	//死亡动画
	auto cbIsSkillsBomb = CallFunc::create([=](){isSkillsBomb(this->sb); });
	auto cbRemove = CallFunc::create(std::bind(&BaseEnemy::removeEnemyNode, this));

	this->runAction(Sequence::create(enemyDie(),cbIsSkillsBomb,cbRemove,NULL));

	auto center = __NotificationCenter::getInstance();
	center->postNotification("EnemyDie", this);

	
}

//受伤动画
void BaseEnemy::enemyHurt(){
	//受伤动画
	auto sp = Sprite::create();
	sp->setAnchorPoint(Vec2(0, 0));
	sp->setPosition(0, 20);
	this->addChild(sp);
	auto ani = ShareFunc::getAct("EnemyHurt1.png", 1, 6, 0.2, 1);
	auto cf = CallFunc::create([=](){
		sp->removeFromParentAndCleanup(true);
	});
	sp->runAction(Sequence::create(ani, cf, NULL));
	
}
//创建子弹
void BaseEnemy::createBullet(std::string fileName){
	auto heroLayer = scene->getHeroLayer();
	auto enemyLayer = scene->getEnemyLayer();
	auto hero = heroLayer->getChildByName("hero");
	auto bullet = QuadrantBullet::create(150 * this->bulletCoefficient, this->getPosition(), 100, fileName, hero->getPosition(), 2);
	EnemyBullets::getInstance()->addBullet(bullet);
	enemyLayer->addChild(bullet);
}
//创建子弹
void BaseEnemy::addFire(float t){
	
	createBullet("EnemyBullet6.png");

}












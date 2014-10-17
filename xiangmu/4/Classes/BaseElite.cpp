#include "BaseElite.h"


bool BaseElite::initWithSpriteFrameName(std::string fileName, int sb, int level) {

	//子类先付初值，然后父类做同意系数相乘。
	this->setEnemySpeed(500);

	this->setHp(50);

	this->setScore(300);

    if (!BaseEnemy::initWithSpriteFrameName(fileName,sb,level))
    {
		return false;
    }


	bulletCount = 0;
	firstCollide = true;
	randomNumber = CCRANDOM_0_1()*200-200;
	return true;
}

void BaseElite::onEnter()
{
	BaseEnemy::onEnter();
	this->setPosition(vSize.width+this->getContentSize().width / 2, vSize.height / 2);
	auto moveBy = MoveBy::create((this->getContentSize().width + vSize.width) / this->getEnemySpeed(), Vec2(-(this->getContentSize().width + vSize.width), 0));
	auto eliteCB = CallFunc::create(std::bind(&BaseElite::removeEnemyNode,this));
	this->runAction(Sequence::create(moveBy,eliteCB,NULL));
	this->schedule(schedule_selector(BaseEnemy::addFire), 0.8 / this->bulletCoefficient, 1.0 * this->bulletCoefficient, 0);
}





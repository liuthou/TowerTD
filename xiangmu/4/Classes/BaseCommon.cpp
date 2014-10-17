#include "BaseCommon.h"
#include "QuadrantBullet.h"
#include "GameScene.h"
#include "EnemyBullets.h"

bool BaseCommon::initWithSpriteFrameName(std::string fileName, int sb, int level)
{
	this->setEnemySpeed(500);

	this->setHp(70);

	this->setScore(100);

	if (!BaseEnemy::initWithSpriteFrameName(fileName, sb, level))
	{
		return false;
	}

	

	enemyType = false;
	randomNumber = CCRANDOM_0_1()*4;
	switch (randomNumber)
	{
	case 0:
		this->setPosition(vSize.width / 5 * 4, -this->getContentSize().height / 2);
		break;
	case 1:
		this->setPosition(vSize.width / 5 * 4, vSize.height + this->getContentSize().height / 2);
		break;
	case 2:
		this->setPosition(vSize.width+this->getContentSize().width/2,vSize.height/3*1);
		break;
	default:
		this->setPosition(vSize.width+this->getContentSize().width/2,vSize.height/3*2);
		break;
	}
	return true;
}

void BaseCommon::onEnter()
{
	BaseEnemy::onEnter();
	//普通敌人的四种路线
	if (randomNumber == 0)
	{
		ccBezierConfig tr0;     //贝塞尔
		tr0.endPosition = Vec2(vSize.width/5*3,vSize.height+this->getContentSize().height/2);    //终点
		tr0.controlPoint_1 = Vec2(vSize.width/2-350,vSize.height/3*2-20);                                             //第一个控制点
		tr0.controlPoint_2 = Vec2(vSize.width+250,vSize.height/3);                                 //第二个控制点
		ActionInterval* bezierForward = BezierTo::create(2000 / this->getEnemySpeed(), tr0);                               //用ccBezierConfig类型的tr0创建贝塞尔曲线
		auto cbCommon = CallFunc::create(std::bind(&BaseCommon::removeEnemyNode,this));
		this->runAction(Sequence::create(bezierForward,cbCommon,NULL));
	}else if(randomNumber == 1)
	{
		ccBezierConfig tr0;    
		tr0.endPosition = Vec2(vSize.width /5*3, -this->getContentSize().height / 2);
		tr0.controlPoint_1 = Vec2(vSize.width / 2-350, vSize.height / 3 +50);
		tr0.controlPoint_2 = Vec2(vSize.width+250,vSize.height/3*2);
		ActionInterval* bezierForward = BezierTo::create(2000 / this->getEnemySpeed(), tr0);
		auto cbCommon = CallFunc::create(std::bind(&BaseCommon::removeEnemyNode, this));
		this->runAction(Sequence::create(bezierForward,cbCommon,NULL));
	}else if (randomNumber == 2)
	{
		auto moveto = MoveTo::create(vSize.width / 4 * 3 / this->getEnemySpeed(), Vec2(vSize.width / 4 * 3, vSize.height / 3));
		ccBezierConfig tr0;    
		tr0.endPosition = Vec2(vSize.width+this->getContentSize().width/2,vSize.height/3*2);
		tr0.controlPoint_1 = Vec2(vSize.width/4,vSize.height/3*2);
		tr0.controlPoint_2 = Vec2(vSize.width/4*3,vSize.height);
		ActionInterval * bezierForward = BezierTo::create(2000 / this->getEnemySpeed(), tr0);
		auto cbCommon = CallFunc::create(std::bind(&BaseCommon::removeEnemyNode, this));
		this->runAction(Sequence::create(moveto,bezierForward,cbCommon,NULL));
	}else if (randomNumber == 3)
	{
		auto moveto = MoveTo::create(vSize.width / 4 * 3 / this->getEnemySpeed(), Vec2(vSize.width / 4 * 3, vSize.height / 3 * 2));
		ccBezierConfig tr0;    
		tr0.endPosition = Vec2(vSize.width+this->getContentSize().width/2,vSize.height/3);
		tr0.controlPoint_1 = Vec2(vSize.width/4,vSize.height/3);
		tr0.controlPoint_2 = Vec2(vSize.width/4*3,0);
		ActionInterval* bezierForward = BezierTo::create(2000 / this->getEnemySpeed(), tr0);
		auto cbCommon = CallFunc::create(std::bind(&BaseCommon::removeEnemyNode, this));
		this->runAction(Sequence::create(moveto,bezierForward,cbCommon,NULL));
	}
	//帧回调发射子弹
	this->schedule(schedule_selector(BaseCommon::addFire), 2 / this->bulletCoefficient);
}






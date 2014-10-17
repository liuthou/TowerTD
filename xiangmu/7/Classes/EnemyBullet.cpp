#include "EnemyBullet.h"
#include "RoleAnimate.h"
#include "GameScene.h"
bool EnemyBullet::init(std::string fileName,Vec2 position)
{
	if (!BaseBullet::init(fileName))
	{
		return false;
	}

	auto rscene = dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene());
	auto layer = rscene->getEnemyLayer();
	layer->addChild(this);
	
	AllVectors::getInstance()->addEnemyBullet(this);

	this->setPosition(position);
	m_position = position;
	vsize = Director::getInstance()->getVisibleSize();
	this->schedule(schedule_selector(EnemyBullet::removeBullet));
	return true;
}

EnemyBullet *EnemyBullet::create(std::string fileName,Vec2 position)
{
	auto enemybullet = new EnemyBullet();
	if(enemybullet && enemybullet->init(fileName,position)){
		enemybullet->autorelease();
		return enemybullet;
	}
	CC_SAFE_DELETE(enemybullet);
	return nullptr;
}

void EnemyBullet::move(int direction){
	if(direction == 1){
		auto moveRight = MoveBy::create((vsize.width - m_position.x + 10)/ENEMYBULLETSPEED,Vec2(vsize.width - m_position.x + 10,0));
		auto ani = getRightBulletAnimate();
		auto spa = Spawn::create(ani,moveRight,nullptr);
		this->runAction(spa);
	}
	if(direction == 2){
		auto moveLeft = MoveBy::create((m_position.x + 10)/ENEMYBULLETSPEED,Vec2(-m_position.x - 10,0));
		auto ani = getLeftBulletAnimate();
		auto spa = Spawn::create(ani,moveLeft,nullptr);
		this->runAction(spa);
	}
}

Animate * EnemyBullet::getRightBulletAnimate(){
	std::vector<std::string>fileNames;
	for (int i = 1;i <= 5;i++){
		auto fileName = StringUtils::format("RightBullet%d.png",i);
		fileNames.push_back(fileName);
	}
	auto ani = RoleAnimate::getinstance()->createAnimate(fileNames,0.1,-1);
	return ani;
}

Animate * EnemyBullet::getLeftBulletAnimate(){
	std::vector<std::string>fileNames;
	for(int i = 1;i <= 5;i++){
		auto fileName = StringUtils::format("LeftBullet%d.png",i);
		fileNames.push_back(fileName);
	}
	auto ani = RoleAnimate::getinstance()->createAnimate(fileNames,0.1,-1);
	return ani;
}

void EnemyBullet::removeBullet(float t){
	if(this->getPositionX() <= 0 || this->getPositionX() >= vsize.width){
		this->removeFromParentAndCleanup(true);
		this->setState(true);
		AllVectors::getInstance()->deleteEnemyBullet();
	}
}
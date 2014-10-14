#include "BaseEnemyplan.h"
#include "GameScene.h"
#include "plans.h"
bool BaseEnemyplan::initWithSpriteFrameName(std::string filename,int Speed,int Hp){
	if(!Sprite::initWithSpriteFrameName(filename)){
		return false;
	}
	//屏幕的size
	Size vSize = Director::getInstance()->getVisibleSize();
	//敌机size
	Size eSize = this->getContentSize();
	this->Speed=Speed;
	this->Hp=Hp;
	//随机位置
	this->setPosition(CCRANDOM_0_1()*(vSize.width-eSize.width)+eSize.width/2 ,vSize.height+eSize.height/2);
	//死亡动画
	void die(std::vector<std::string> fileNames);
	//飞行
	float dis = vSize.height+eSize.height;
	auto move = MoveBy::create(dis/Speed,Vec2(0,-dis));
	//移动完成删除
	auto cf = CallFunc::create(std::bind(&BaseEnemyplan::remove,this));
	this->runAction(Sequence::create(move,cf,NULL));
	this->runAction(move);
	//加入到敌机层
	auto scene = dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene());
	auto elayer = scene->getEnemyLayer();
	elayer->addChild(this);
	//将飞机放入飞机容器
	plans::getInstance()->addplan(this);
	return true;
}
void BaseEnemyplan::die(std::vector<std::string>fileNames){
	auto ani = Animation::create();
	for(auto it:fileNames ){
		auto fram =SpriteFrameCache::getInstance()->getSpriteFrameByName(it);
		ani->addSpriteFrame(fram);
		ani->setDelayPerUnit(0.1);
		ani->setLoops(1);
		//游戏动作完成时会回调绑定的函数
		auto cf = CallFunc::create(std::bind(&BaseEnemyplan::remove,this));

		this->runAction(Sequence::create(Animate::create(ani),cf,NULL));

	}
}
void BaseEnemyplan::remove(){
	this->removeFromParentAndCleanup(true);
}
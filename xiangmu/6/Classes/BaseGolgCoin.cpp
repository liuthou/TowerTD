#include "BaseGoldCoin.h"
#include "PlayGameScene.h"
#include "HitBodys.h"
#include "AudioUtil.h"

bool BaseGoleCoin::init(std::string fileName, int id_x, int id_y){
	if (!BaseRewards::initWithFile(fileName)){
		return false;
	}
	m_id_x = id_x;
	m_id_y = id_y;
	return true;
}
BaseGoleCoin * BaseGoleCoin::create(std::string fileName, int id_x, int id_y){
	BaseGoleCoin * bs = new BaseGoleCoin();
	if (bs && bs->init(fileName, id_x, id_y)){
		bs->autorelease();
		return bs;
	}
	CC_SAFE_DELETE(bs); 
	return nullptr;
}
void BaseGoleCoin::collisionRole(){
    AudioUtil::getInstance() -> playEffect("gold.mp3");
    
}
void BaseGoleCoin::onEnter(){

	BaseRewards::onEnter();
	changeRoleState();
	addAnimation();
}

void BaseGoleCoin::addAnimation(){
	auto leftRote = RotateBy::create(1, Vec3(0,40,0));
	auto rightRote = RotateBy::create(1, Vec3(0,-40,0));
	auto linkLeftRight = Sequence::create(leftRote, rightRote, NULL);
	this->runAction(RepeatForever::create(linkLeftRight));
}

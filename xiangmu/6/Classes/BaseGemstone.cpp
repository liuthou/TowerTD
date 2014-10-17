#include "BaseGemstone.h"
#include "PlayGameScene.h"
#include "HitBodys.h"
bool BaseGemstone::init(std::string fileName,int id_x,int id_y){
	if (!BaseRewards::initWithFile(fileName)){
		return false;
	}
	m_id_x = id_x;
	m_id_y = id_y;
	return true;
}
BaseGemstone * BaseGemstone::create(std::string fileName,int id_x,int id_y){
	BaseGemstone * ba = new BaseGemstone();
	if (ba && ba->init(fileName,id_x,id_y)){
		ba->autorelease();
		return ba;
	}
	CC_SAFE_DELETE(ba);
	return nullptr;
}
void BaseGemstone::onEnter(){
	BaseRewards::onEnter();
	changeRoleState();
    addAnimation();
}
void BaseGemstone::addAnimation(){
	auto ani = Blink::create(0.5,1);
	this->setVisible(true);
	this->runAction(RepeatForever::create(ani));
}
//void BaseGemstone::changeRoleState(){
//	/*vSize = Director::getInstance()->getVisibleSize();
//	pSize = this->getContentSize();
//
//	if (m_id_x = 1){
//	x = vSize.width/3 - pSize.width + pSize.width/2;
//	}
//	if (m_id_x = 2){
//	x = vSize.width * 2/3 - pSize.width + pSize.width/2;
//	}
//	if (m_id_x = 3){
//	x = vSize.width - pSize.width + pSize.width/2;
//	}
//	if (m_id_y = 1){
//	y = vSize.height/3 - pSize.height + pSize.height/2;
//	}
//	if (m_id_y = 2){
//	y = vSize.height * 2/3 - pSize.height + pSize.height/2;
//	}
//	if (m_id_y = 3){
//	y = vSize.height - pSize.height + pSize.height/2;
//	}
//	this->setPosition(x,y);*/
//
//	
//}
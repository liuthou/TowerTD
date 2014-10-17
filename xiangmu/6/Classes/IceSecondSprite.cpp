#include "IceSecondSprite.h"
#include "HitBodys.h"
#include "JumpHelp.h"
bool IceSecondSprite::init(std::string fileName){
	if (!ToolsBaseControlUserScript::init()){
		return false;
	}
	this->setTexture(fileName);
    this -> scheduleOnce(schedule_selector(IceSecondSprite::removeIce), 0.5);
	return true;
}
void IceSecondSprite::removeIce(float ft){
    this -> removeFromParentAndCleanup(true);
}
IceSecondSprite * IceSecondSprite::create(std::string fileName){
	IceSecondSprite * iss = new IceSecondSprite();
	if (iss && iss->init(fileName)){
		iss->autorelease();
		return iss;
	}
	CC_SAFE_DELETE(iss);
	return nullptr;
}
void IceSecondSprite::changeRoleState(){

}

Direction_ROLE IceSecondSprite::collitionDirection(){
	return Direction_ROLE::LEFT;
}

int IceSecondSprite::controleRoleSpeed(){
	return NO_CHANGE_ROLE_SPEED;
}

void IceSecondSprite::collisionRole(){
    
}
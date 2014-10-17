#include "BaseRewards.h"
#include "PlayGameScene.h"
#include "HitBodys.h"
#include "AudioUtil.h"
bool BaseRewards::initWithFile(std::string fileName){

	if (!ToolsBaseScript::initWithFile(fileName)){
		return false;
	}

	vSize = Director::getInstance()->getVisibleSize();
	pSize = this->getContentSize();
	x = 0;
	y = 0;
	m_id_x = 0;
	m_id_y = 0;
    HitBodys::getInstance()->addToolsBaseControlUserScript(this);
	return true;

}
void BaseRewards::collisionRole(){
    AudioUtil::getInstance() -> playEffect("gold.mp3");
}
 void BaseRewards::removeDieSprite(){

	 this->setDie(true);
	 __NotificationCenter::getInstance()->postNotification("Award");
	 this->removeFromParentAndCleanup(true);

 }

Direction_ROLE BaseRewards::collitionDirection(){
    return Direction_ROLE::UP;
}

int BaseRewards::controleRoleSpeed(){
    return NO_CHANGE_ROLE_SPEED;
}

 void BaseRewards::onEnter(){
	 ToolsBaseScript::onEnter();
	 changeRoleState();
	 if (isMove == true){
		 addMagnetAnimation();
	 }
 }
std::string BaseRewards::sendCast(){
    return EAT_GOLD_REWARD_USER;
}
 void BaseRewards::addMagnetAnimation(){
	 SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fazhen9.plist");
	 Animation * ani = Animation::create();
	 for (int i = 0;i < 18;i++){
		 std::string fileName = StringUtils::format("%d.png",i);
		 ani->addSpriteFrameWithFile(fileName);
	 }
	 ani->setDelayPerUnit(0.1);
	 ani->setLoops(-1);
	 Animate * amt = Animate::create(ani);
	 this->runAction(amt);
 }

 void BaseRewards::changeRoleState(){
	

	 /* if (1 == m_id_x && 1 == m_id_y){
	 x = pSize.width;
	 y = vSize.height/3 - pSize.height + pSize.height/2;
	 this->setPosition(x,y);
	 }*/

	 if (1 == m_id_x && 2 == m_id_y){
		 x = pSize.width;
		 y = vSize.height * 2/3 - pSize.height + pSize.height/2;
		 this->setPosition(x,y);
	 }
	 if (1 == m_id_x && 3 == m_id_y){
		 x = pSize.width/2;
		 y = vSize.height - pSize.height + pSize.height/2;
		 this->setPosition(x,y);
	 }
	 if (1 == m_id_x && 4 == m_id_y){
		 x = pSize.width;
		 y = pSize.height/2;
		 this->setPosition(x,y);
	 }




	 if (2 == m_id_x && 1 == m_id_y){
		 x = vSize.width/3 - pSize.width + pSize.width/2;
		  y = vSize.height/3 - pSize.height + pSize.height/2;
		  this->setPosition(x,y);
	 }
	 if (2 == m_id_x && 2 == m_id_y){
		 x = vSize.width/3 - pSize.width + pSize.width/2;
		  y = vSize.height * 2/3 - pSize.height + pSize.height/2;
		  this->setPosition(x,y);
	 }
	 if (2 == m_id_x && 3 == m_id_y){
		 x = vSize.width/3 - pSize.width + pSize.width/2;
		 y = vSize.height - pSize.height + pSize.height/2;
		 this->setPosition(x,y);
	 }
	 if (2 == m_id_x && 4 == m_id_y){
		 x = vSize.width/3 - pSize.width + pSize.width/2;
		 y = pSize.height/2;
		 this->setPosition(x,y);
	 }





	 if (3 == m_id_x && 1 == m_id_y){
		 x = vSize.width * 2/3 - pSize.width + pSize.width/2;
		 y = vSize.height/3 - pSize.height + pSize.height/2;
		 this->setPosition(x,y);
	 }
	 if (3 == m_id_x && 2 == m_id_y){
		 x = vSize.width * 2/3 - pSize.width + pSize.width/2;
		 y = vSize.height * 2/3 - pSize.height + pSize.height/2;
		 this->setPosition(x,y);
	 }
	 if (3 == m_id_x && 3 == m_id_y){
		 x = vSize.width * 2/3 - pSize.width + pSize.width/2;
		 y = vSize.height - pSize.height + pSize.height/2;
		 this->setPosition(x,y);
	 }
	 if (3 == m_id_x && 4 == m_id_y){
		 x = vSize.width * 2/3 - pSize.width + pSize.width/2;
		 y = pSize.height/2;
		 this->setPosition(x,y);
	 }




	 if (4 == m_id_x && 1 == m_id_y){
		 x = vSize.width - pSize.width + pSize.width/2;
		 y = vSize.height/3 - pSize.height + pSize.height/2;
		 this->setPosition(x,y);
	 }
	 if (4 == m_id_x && 2 == m_id_y){
		  x = vSize.width - pSize.width + pSize.width/2;
		  y = vSize.height * 2/3 - pSize.height + pSize.height/2;
		  this->setPosition(x,y);
	 }
	 if (4 == m_id_x && 3 == m_id_y){
		  x = vSize.width - pSize.width + pSize.width/2;
		  y = vSize.height - pSize.height + pSize.height/2;
		  this->setPosition(x,y);
	 }
	 /* if (4 == m_id_x && 4 == m_id_y){
	 x = vSize.width - pSize.width + pSize.width/2;
	 y = pSize.height/2;
	 this->setPosition(x,y);
	 }*/

 }
 
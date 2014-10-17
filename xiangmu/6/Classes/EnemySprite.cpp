#include "EnemySprite.h"
#include "ConfigUtil.h"
#include "HitBodys.h"
#include "JumpHelp.h"
#include "AudioUtil.h"
bool EnemySprite::init(){
	if (!ToolsBaseControlUserScript::init()){
		return false;
	}
	
	vSize = Director::getInstance()->getVisibleSize();
	pSize = this->getContentSize();
	this->setScale(0.5);
	m_speed = 100;
    auto spFirst = MoveBy::create((vSize.width/2)/m_speed,Vec2(vSize.width/2 - pSize.width/2,-vSize.height/2+pSize.height/2));
    auto spSecond = MoveBy::create((vSize.width)/m_speed,Vec2(-vSize.width + pSize.width,-vSize.height/2+pSize.height/2));
    auto spThree = MoveBy::create((vSize.width - pSize.width)/m_speed,Vec2(vSize.width - pSize.width,-vSize.height/2+pSize.height/5));
    auto setdie = CallFunc::create([=](void){
        this->die();
    });
    auto poo = Sequence::create(spFirst,spSecond,spThree,setdie,NULL);
    this->runAction(poo);
	HitBodys::getInstance()->addToolsBaseControlUserScript(this);
    this -> setDie(false);
	return true;
}
EnemySprite * EnemySprite::create(std::string fileName){
    EnemySprite *pRet = new EnemySprite();
    if (pRet && pRet->init())
    {
        pRet->setTexture(fileName);
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
void EnemySprite::collisionRole(){
    AudioUtil::getInstance() -> playEffect("shit.wav");
    
	JumpHelp::getRoleSprite() -> hitIce();
    
}
void EnemySprite::changeRoleState(){

 }

Direction_ROLE EnemySprite::collitionDirection(){
	return Direction_ROLE::UP;
}
std::string EnemySprite::sendCast(){
    return SHIT_ENEMY_HIT_ROLE;
}
int EnemySprite::controleRoleSpeed(){
	return NO_CHANGE_ROLE_SPEED;
}


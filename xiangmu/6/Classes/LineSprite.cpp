#include "LineSprite.h"
#include "HitBodys.h"
#include "JumpHelp.h"
#include "AudioUtil.h"
bool LineSprite::init(std::string fileName){
	if (!ToolsBaseControlUserScript::init()){
		return false;
	}
	this->setTexture(fileName);
	this->setScale(1.2);
	HitBodys::getInstance()->addToolsBaseControlUserScript(this);
	changeRoleState();
	return true;
}

LineSprite * LineSprite::create(std::string fileName){
	LineSprite * ls = new LineSprite();
	if (ls && ls->init(fileName)){
		ls->autorelease();
		return ls;
	}
	CC_SAFE_DELETE(ls);
	return nullptr; 
}

Direction_ROLE LineSprite::collitionDirection(){
	return Direction_ROLE::UP;
}

int LineSprite::controleRoleSpeed(){
	return NO_CHANGE_ROLE_SPEED;
}
std::string LineSprite::sendCast(){
    return DOU_ENEMY_HIT_ROLE;
}
void LineSprite::collisionRole(){
    JumpHelp::getRoleSprite() -> hitDoubi();
    AudioUtil::getInstance() ->playEffect("dou.wav");
}

void LineSprite::changeRoleState(){
	auto jp = JumpBy::create(5,Vec2(0,0),50,7);
	auto sq = DelayTime::create(2);
	auto sf = CallFunc::create([=](void){
		this->die();
	});
	auto sff = Sequence::create(jp,sq,sf,NULL);
	this->runAction(sff);
}


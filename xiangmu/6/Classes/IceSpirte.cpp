#include "IceSprite.h"
#include "HitBodys.h"
#include "JumpHelp.h"
#include "AudioUtil.h"
bool IceSprite::init(std::string fileName,int m_id){
	if (!ToolsBaseControlUserScript::init()){
		return false;
	}
	this->setTexture(fileName);
	vSize = Director::getInstance()->getVisibleSize();
	pSize = this->getContentSize();
	m_speed = 50;
	m_number = m_id;
	changeRoleState();
	HitBodys::getInstance()->addToolsBaseControlUserScript(this);
	return true;

}
IceSprite * IceSprite::create(std::string fileName,int m_id){
	IceSprite * ice = new IceSprite();
		if (ice && ice->init(fileName,m_id)){
		ice->autorelease();
		return ice;	
	}
	CC_SAFE_DELETE(ice);
	return nullptr;
}
Direction_ROLE IceSprite::collitionDirection(){
	return Direction_ROLE::UP;
}
int IceSprite::controleRoleSpeed(){
	return NO_CHANGE_ROLE_SPEED;
}
void IceSprite::collisionRole(){
	JumpHelp::getRoleSprite() -> hitIce();
    AudioUtil::getInstance() -> playEffect("ice.mp3");
}
void IceSprite::changeRoleState(){

	if (1 == m_number){
		auto sp = MoveBy::create(vSize.width/m_speed,Vec2(vSize.width - pSize.width/2,0));
		Animation * ani = Animation::create();
		std::string fileName;
		for (int i = 11;i < 18;i++){
			fileName = StringUtils::format("%d.png",i);
			ani->addSpriteFrameWithFile(fileName);
		}
		ani->setDelayPerUnit(0.1);
		ani->setLoops(-1);
		auto amt = Animate::create(ani);
		auto sf = Spawn::create(sp,amt,NULL);
		auto setdie = CallFunc::create([=](void){
			this->setDie(true);
			this->removeFromParentAndCleanup(true);
		});
		auto sff = Sequence::create(sf,setdie,NULL);
		this->runAction(sff);
	}

	if (2 == m_number){
		auto sp = MoveBy::create(vSize.width/m_speed,Vec2(vSize.width - pSize.width/2,vSize.height/4));
		Animation * ani = Animation::create();
		std::string fileName;
		for (int i = 11;i < 18;i++){
			fileName = StringUtils::format("%d.png",i);
			ani->addSpriteFrameWithFile(fileName);
		}
		ani->setDelayPerUnit(0.1);
		ani->setLoops(-1);
		auto amt = Animate::create(ani);
		auto sf = Spawn::create(sp,amt,NULL);
		auto setdie = CallFunc::create([=](void){
			this->setDie(true);
			this->removeFromParentAndCleanup(true);
		});
		auto sff = Sequence::create(sf,setdie,NULL);
		this->runAction(sff);
	}

	if (3 == m_number){
		auto sp = MoveBy::create(vSize.width/m_speed,Vec2(vSize.width - pSize.width/2,-vSize.height/2));
		Animation * ani = Animation::create();
		std::string fileName;
		for (int i = 11;i < 18;i++){
			fileName = StringUtils::format("%d.png",i);
			ani->addSpriteFrameWithFile(fileName);
		}
		ani->setDelayPerUnit(0.1);
		ani->setLoops(-1);
		auto amt = Animate::create(ani);
		auto sf = Spawn::create(sp,amt,NULL);
		auto setdie = CallFunc::create([=](void){
			this->setDie(true);
			this->removeFromParentAndCleanup(true);
		});
		auto sff = Sequence::create(sf,setdie,NULL);
		this->runAction(sff);
	}

	if (4 == m_number){
		auto sp = MoveBy::create(vSize.width/m_speed,Vec2(-vSize.width - pSize.width/2,0));
		Animation * ani = Animation::create();
		std::string fileName;
		for (int i = 11;i < 18;i++){
			fileName = StringUtils::format("%d.png",i);
			ani->addSpriteFrameWithFile(fileName);
		}
		ani->setDelayPerUnit(0.1);
		ani->setLoops(-1);
		auto amt = Animate::create(ani);
		auto sf = Spawn::create(sp,amt,NULL);
		auto rt = RotateBy::create(0.1,Vec3(0,180,0));
		auto setdie = CallFunc::create([=](void){
			this->die();
		});
		auto sff = Sequence::create(rt,sf,setdie,NULL);
		this->runAction(sff);
	}

	if (5 == m_number){
		auto sp = MoveBy::create(vSize.width/m_speed,Vec2(-vSize.width - pSize.width/2,vSize.height/4));
		Animation * ani = Animation::create();
		std::string fileName;
		for (int i = 11;i < 18;i++){
			fileName = StringUtils::format("%d.png",i);
			ani->addSpriteFrameWithFile(fileName);
		}
		ani->setDelayPerUnit(0.1);
		ani->setLoops(-1);
		auto amt = Animate::create(ani);
		auto sf = Spawn::create(sp,amt,NULL);
		auto rt = RotateBy::create(0.1,Vec3(0,180,0));
		auto setdie = CallFunc::create([=](void){
			this->die();
		});
		auto sff = Sequence::create(rt,sf,setdie,NULL);
		this->runAction(sff);
	}

	if (6 == m_number){
		auto sp = MoveBy::create(vSize.width/m_speed,Vec2(-vSize.width - pSize.width/2,-vSize.height/4));
		Animation * ani = Animation::create();
		std::string fileName;
		for (int i = 11;i < 18;i++){
			fileName = StringUtils::format("%d.png",i);
			ani->addSpriteFrameWithFile(fileName);
		}
		ani->setDelayPerUnit(0.1);
		ani->setLoops(-1);
		auto amt = Animate::create(ani);
		auto sf = Spawn::create(sp,amt,NULL);
		auto rt = RotateBy::create(0.1,Vec3(0,180,0));
		auto setdie = CallFunc::create([=](void){
			this->die();
		});
		auto sff = Sequence::create(rt,sf,setdie,NULL);
		this->runAction(sff);
	}
}


std::string IceSprite::sendCast(){
    return GOST_EMEMY_HIT_ROLE;
}
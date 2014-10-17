#include "EnemyBase.h"
EnemyBase::EnemyBase()
:m_maxhp(0)
,m_curhp(0)
,m_money(0)
,m_speed(0)
,m_origspeed(0)
,m_isstop(false)
,m_hurtproperty(NIRGUNA)
,m_lifestate(NORMAL)
,m_direction(UP)
{}
EnemyBase::~EnemyBase(){}
bool EnemyBase::init(float hp,float speed){
	if(!Sprite::init()){
		return false;
	}
	this->m_maxhp=hp;
	this->m_origspeed=speed;
	this->m_speed=speed;
	this->m_curhp=m_maxhp;
	return true;
}
void EnemyBase::remove(){
	this->removeFromParentAndCleanup(true);
}

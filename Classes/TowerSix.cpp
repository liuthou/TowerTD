#include "TowerSix.h"
#include "FireSkill.h"


bool TowerSix::init( )
{
	if(!BaseTower::init())
	{
		return false;
	}

	this->setScope(200);
	this->setSpeed(1);
	   
	return  true;
}

void TowerSix::Attack(float t){
	if (soldier!=NULL){
		 
			this->runAnimate("Animation6");
	 
		auto bullet =FireSkill::create(this->getPosition(),targetpoint);
	}
}
void TowerSix::stopAnm()
{
	this->runAnimate("Animation6NULL");
}





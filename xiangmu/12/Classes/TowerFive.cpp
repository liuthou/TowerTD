#include "TowerFive.h"
#include "WindSkill.h"


bool TowerFive::init( )
{
	if(!BaseTower::init())
	{
		return false;
	}

	this->setScope(200);
	this->setSpeed(1);
	    
	return  true;
}

void TowerFive::Attack(float t){
	if (soldier!=NULL){
		 
			this->runAnimate("Animation5");
		 
		auto bullet =WindSkill::create(targetpoint);
	}
}
void TowerFive::stopAnm()
{
	this->runAnimate("Animation5NULL");
}





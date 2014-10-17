#include "TowerFour.h"
#include "YellowThunder.h"

bool TowerFour::init( )
{
	if(!BaseTower::init())
	{
		return false;
	}

	this->setScope(150);
	this->setSpeed(1.5);
	  
	return  true;
}

void TowerFour::Attack(float t){
	if (soldier!=NULL){
		 
			this->runAnimate("Animation4");
		 
		auto bullet =YellowThunder::create(targetpoint);
	}
}
void TowerFour::stopAnm()
{
	this->runAnimate("Animation4NULL");
}





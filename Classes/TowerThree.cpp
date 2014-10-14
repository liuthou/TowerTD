#include "TowerThree.h"
#include "IceSkill.h"


bool TowerThree::init( )
{
	if(!BaseTower::init())
	{
		return false;
	}

	this->setScope(200);
	this->setSpeed(2);
	    
	return  true;
}

void TowerThree::Attack(float t){
	if (soldier!=NULL){
		 
			this->runAnimate("Animation3");
		 
		auto bullet =IceSkill::create(this->getPosition(),targetpoint);
	}
}
void TowerThree::stopAnm()
{
	this->runAnimate("Animation3NULL");
}





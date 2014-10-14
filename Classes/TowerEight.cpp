#include "TowerEight.h"
#include "BigArrow.h"


bool TowerEight::init( )
{
	if(!BaseTower::init())
	{
		return false;
	}

	this->setScope(200);
	this->setSpeed(1);
	   
	return  true;
}

void TowerEight::Attack(float t){
	if (soldier!=NULL){
		if (soldier->getPositionX()<=this->getPositionX())
		{
			this->runAnimate("Animation8Left");
		}else{
			this->runAnimate("Animation8Right");
		}
		auto bullet =BigArrow::create(this->getPosition(),targetpoint);
	}
}
void TowerEight::stopAnm()
{
	this->runAnimate("Animation8NULL");
}





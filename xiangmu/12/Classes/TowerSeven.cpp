#include "TowerSeven.h"
#include "BoneSkill.h"


bool TowerSeven::init( )
{
	if(!BaseTower::init())
	{
		return false;
	}

	this->setScope(200);
	this->setSpeed(1);
	   
	return  true;
}

void TowerSeven::Attack(float t){
	if (soldier!=NULL){
		
		this->runAnimate("Animation7");
		
		auto bullet =BoneSkill::create(this->getPosition(),targetpoint);
	}
}
void TowerSeven::stopAnm()
{
	this->runAnimate("Animation7NULL");
}





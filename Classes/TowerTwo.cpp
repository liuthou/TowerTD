#include "TowerTwo.h"
#include "YellowThunder.h"
#include "ThunderSkill.h"

bool TowerTwo::init( )
{
	if(!BaseTower::init())
	{
		return false;
	}

	this->setScope(200);
	this->setSpeed(1.5);
	    
	return  true;
}

void TowerTwo::Attack(float t){
	 
			this->runAnimate("Animation2Lighting");
		 
		auto bullet = ThunderSkill::create(targetpoint);	 
}
void TowerTwo::stopAnm()
{
	this->runAnimate("Animation2NULL");
}





#include "TowerOne.h"
#include "ArrowSkill.h"
 
 
bool TowerOne::init( )
{
	if(!BaseTower::init())
	{
		return false;
	}
 
	this->setScope(100);
	this->setSpeed(1.5);
	
	return  true;
}

 void TowerOne::Attack(float t){
	 if (soldier!=NULL){
		 if (soldier->getPositionX()<=this->getPositionX())
		 {
			 this->runAnimate("Animation1Left");
		 }else{
			 this->runAnimate("Animation1Right");
		 }
		 auto bullet =ArrowSkill::create(this->getPosition(),targetpoint);
	 }
 }
 void TowerOne::stopAnm()
 {
	 this->runAnimate("Animation1NULL");
 }


 

 
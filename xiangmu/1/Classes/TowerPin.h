#pragma once 
#include "TowerBase.h"
class TowerPin :public TowerBase
{
protected:
	int const rId = 28;
	//void chooseAtkTarget();
	void fire(float dt);
	//void missAtkTarget();
	virtual bool init();
public:

	CREATE_FUNC(TowerPin);
};
#pragma once
#include "BulletBase.h"
class  BulletPin :public BulletBase
{	

	friend class TowerPin;

protected:
	void doAction();
	void doMove()override;
	virtual bool init(const int &rId,VictimEntityBase *rVictimEntity);
	static BulletPin * create(const int &rId,VictimEntityBase * rVictimEntity);

};

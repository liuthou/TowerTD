#pragma once
#include "BulletBase.h"
class BulletAnchor :public BulletBase
{

	friend class TowerAnchor;

protected:
	void doAction();
	void doMove()override;
	virtual bool init(const int &rId, VictimEntityBase *rVictimEntity);
	static BulletAnchor * create(const int &rId, VictimEntityBase * rVictimEntity);

};

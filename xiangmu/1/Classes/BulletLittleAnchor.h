#pragma once
#include "BulletAnchor.h"
class BulletLittleAnchor :public BulletAnchor
{

protected:

	virtual bool init(const int &rId, VictimEntityBase *rVictimEntity);
	static BulletLittleAnchor * create(const int &rId, VictimEntityBase * rVictimEntity);

};

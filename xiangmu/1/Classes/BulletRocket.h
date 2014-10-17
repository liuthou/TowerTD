#ifndef __CarrotFantasy__BulletRocket__
#define __CarrotFantasy__BulletRocket__
#include "BulletBase.h"
class VictimEntityBase;

class BulletRocket :public BulletBase{

	friend class TowerRocket;

protected:

	void doAction();

	void doMove()override;

	virtual bool init(const int &rId, VictimEntityBase *rVictimEntity);

	static BulletRocket * create(const int &rId, VictimEntityBase *rVictimEntity);
};
#endif /* defined(__CarrotFantasy__BulletRocket__) */
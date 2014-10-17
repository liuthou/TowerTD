#ifndef __CarrotFantasy__BulletStar__
#define __CarrotFantasy__BulletStar__
#include "BulletBase.h"
class VictimEntityBase;

class BulletStar :public BulletBase{

	friend class TowerStar;

protected:

	void doAction();

	void doMove()override;

	virtual bool init(const int &rId,VictimEntityBase *rVictimEntity);

	static BulletStar * create(const int &rId, VictimEntityBase *rVictimEntity);
};
#endif /* defined(__CarrotFantasy__BulletStar__) */
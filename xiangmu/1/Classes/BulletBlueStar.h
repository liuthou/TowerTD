#ifndef __CarrotFantasy__BulletBlueStar__
#define __CarrotFantasy__BulletBlueStar__
#include "BulletBase.h"
class VictimEntityBase;

class BulletBlueStar :public BulletBase{

	friend class TowerBlueStar;

protected:

	void doAction();

	void doMove()override;

	virtual bool init(const int &rId, VictimEntityBase *rVictimEntity);

	static BulletBlueStar * create(const int &rId, VictimEntityBase *rVictimEntity);
};
#endif /* defined(__CarrotFantasy__BulletBlueStar__) */
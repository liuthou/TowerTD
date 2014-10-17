#ifndef __CarrotFantasy__TowerStar__
#define __CarrotFantasy__TowerStar__
#include "TowerBase.h"
class TowerStar :public TowerBase{

	int const rId = 13;

	virtual bool init();

	virtual void fire(float dt);

public:

	CREATE_FUNC(TowerStar);
};
#endif /* defined(__CarrotFantasy__TowerStar__) */
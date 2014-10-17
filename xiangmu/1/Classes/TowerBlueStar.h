#ifndef __CarrotFantasy__TowerBlueStar__
#define __CarrotFantasy__TowerBlueStar__
#include "TowerBase.h"
class TowerBlueStar :public TowerBase{

	int const rId = 19;

	virtual bool init();

	virtual void fire(float dt);

public:

	CREATE_FUNC(TowerBlueStar);
};
#endif /* defined(__CarrotFantasy__TowerBlueStar__) */
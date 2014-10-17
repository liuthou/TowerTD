#ifndef __CarrotFantasy__TowerRocket__
#define __CarrotFantasy__TowerRocket__
#include "TowerBase.h"
class TowerRocket :public TowerBase{

	int const rId = 25;

	virtual bool init();

	virtual void fire(float dt);

public:

	CREATE_FUNC(TowerRocket);
};
#endif /* defined(__CarrotFantasy__TowerRocket__) */
#ifndef __CarrotFantasy__TowerBall__
#define __CarrotFantasy__TowerBall__
#include "TowerBase.h"

class TowerBall :public TowerBase{
protected:

	virtual bool init();

	void  chooseAtkTarget();

	void fire(float dt);

	void missAtkTarget();

	int const rId = 10;

	Sprite * _doActionSprite;

public:

	CREATE_FUNC(TowerBall);

};
#endif
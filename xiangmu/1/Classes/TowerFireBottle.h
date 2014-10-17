#ifndef __CarrotFantasy__TowerFireBottle__
#define __CarrotFantasy__TowerFireBottle__
#include "TowerBase.h"

class TowerFireBottle :public TowerBase{
protected:

	virtual bool init();

	void  chooseAtkTarget();

	void missAtkTarget();

	void fire(float dt);

	int const rId = 16;

	Sprite * _doActionSprite;

public:

	CREATE_FUNC(TowerFireBottle);

};
#endif
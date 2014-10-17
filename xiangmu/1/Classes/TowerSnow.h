#ifndef __CarrotFantasy__TowerSnow__
#define __CarrotFantasy__TowerSnow__
#include "TowerBase.h"
class TowerSnow :public TowerBase{

	int const rId = 31;

	virtual bool init();

	virtual void fire(float dt);

	Sprite * _doAnimationSprite;

	void attack();

public:

	CREATE_FUNC(TowerSnow);
};
#endif /* defined(__CarrotFantasy__TowerSnow__) */
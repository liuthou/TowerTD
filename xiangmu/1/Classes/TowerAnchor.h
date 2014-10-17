#pragma once 
#include "TowerBase.h"
class TowerAnchor:public TowerBase
{
private:
	Sprite * _doActionSprite;
	int const rId = 37;
	void fire(float dt);
	virtual bool init();
public:
	CREATE_FUNC(TowerAnchor);
};

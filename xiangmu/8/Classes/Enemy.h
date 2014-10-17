#pragma once

#include "AppMacro.h"
#include "BaseAirObject.h"

class Enemy : public BaseAirObject{
private:
	char *textures[4];

	Enemy();

protected:
	virtual bool init();

	void initPhysicsBody(int index);

public:
	virtual void effectWhileCollision(Ref *obj);

	CREATE_FUNC(Enemy);

	void move();
};


#ifndef __Dota_Legend__bondingBox__
#define __Dota_Legend__bondingBox__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;
class bondingBox :public Layer
{
public:
	CREATE_FUNC(bondingBox);
protected:
	virtual bool init();
	void setAttackLayerVisible();
private:
	void Role_To_EnemyBonding(float t);
	void Enemy_To_RoleBonding(float t);
	void RoleBullets_To_Enemy(float t);
	void EnemyBullets_To_Role(float t);
	void Enemy_And_Role(float t);
};
#endif /* defined(__Dota_Legend__bondingBox__) */

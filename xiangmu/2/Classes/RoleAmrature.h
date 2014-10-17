#ifndef _ROLEAMRATURE_H
#define _ROLEAMRATURE_H

#include "cocos2d.h"

using namespace cocos2d;

class RoleAmrature 
{
public:
	static RoleAmrature * getInstance();
	CC_SYNTHESIZE_PASS_BY_REF(int, roleLevel,RoleLevel);
	CC_SYNTHESIZE_PASS_BY_REF(int, roleExp, RoleExp);
	CC_SYNTHESIZE_PASS_BY_REF(int, roleMoney, RoleMoney);
protected:

private:
	static RoleAmrature * roleAmrature;
	RoleAmrature(){};
	RoleAmrature(const RoleAmrature & roleamrature){};
	RoleAmrature operator = (const RoleAmrature &roleamrature){ return roleamrature; };
	~RoleAmrature();

};
#endif
#ifndef __MONSTERSOLDIER_R_
#define __MONSTERSOLDIER_R_
#include "AnimateClass.h"
#include "MonsterBase.h"
#include "cocos2d.h"
#include <iostream>
using namespace std;
using namespace cocos2d;

class MonsterSoldier: public MonsterBase
{
private:
	std::string xmlname;
	AnimateClass * ani;
public:
	virtual bool init(std::string filename);
	static MonsterSoldier *create(std::string filename);	
};

#endif
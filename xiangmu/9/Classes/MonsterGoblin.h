#ifndef __MONSTERGOBLIN_R_
#define __MONSTERGOBLIN_R_
 
#include "MonsterBase.h"
#include "cocos2d.h"
#include <iostream>
#include "AnimateClass.h"
using namespace std;
using namespace cocos2d;
 
class MonsterGoblin : public MonsterBase
{
private:
	std::string xmlname;
	AnimateClass *ani;
public:
	virtual bool init(std::string filename);
	static MonsterGoblin *create(std::string filename);
};
 
#endif
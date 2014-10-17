#ifndef __MonsterBoss_R_
#define __MonsterBoss_R_

#include "MonsterBase.h"
#include "cocos2d.h"
#include <iostream>
#include "AnimateClass.h"
using namespace std;
using namespace cocos2d;

class MonsterBoss : public MonsterBase
{
private:
	std::string xmlname;
public:
	virtual bool init(std::string filename);
	static MonsterBoss *create(std::string filename);
	AnimateClass *ani;
};

#endif
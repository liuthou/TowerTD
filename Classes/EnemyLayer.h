#ifndef __ENEMYLAYER_H
#define __ENEMYLAYER_H
#include "cocos2d.h"
using namespace cocos2d;
class Enemylayer:public Layer{
protected:
	int count; //wave count
	int round;//round count
	int number;//type number
	bool isContinue;
	std::vector<ValueMap> enemyGroup;// all enemy 
	ValueVector enemyRound;// a wave 
	ValueMap roleInfo;
	void addEnemys(std::string type,int enemys,float delaytime);
	void addEnemyRound();
	void addEnemyGroup();
	void update(float t);
	
public:
	virtual bool init();
	CREATE_FUNC(Enemylayer);
	
};
#endif
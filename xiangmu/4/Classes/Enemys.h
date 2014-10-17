#ifndef __ENEMYS__
#define __ENEMYS__

#include "BaseEnemy.h"

//µÐ»úÈÝÆ÷µ¥Àý
class Enemys{
private:
	Enemys(){}
	Enemys(const Enemys & b){}
	Enemys operator=(const Enemys & b){
		return b;
	}
protected:
	//    Vector<BaseEnemy *> enemyVector;
	static Enemys * instance;
public:
	CC_SYNTHESIZE_PASS_BY_REF(Vector<BaseEnemy *>, enemyVector, EnemyVector);
	static Enemys * getInstance();
	void addEnemy(BaseEnemy * enemy);
	void deleteEnemy();
	void reset();
};
#endif 
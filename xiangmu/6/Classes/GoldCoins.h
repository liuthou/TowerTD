#ifndef __GOLDCOINS_H_
#define __GOLDCOINS_H_
#include "cocos2d.h"
#include "BaseGoldCoin.h"
using namespace cocos2d;
class GoldCoins{
private:
	GoldCoins(){}
	GoldCoins(const GoldCoins & g){}
	GoldCoins operator = (const GoldCoins & g){
		return g;
	}
protected:

	static GoldCoins * instance;

public:

	static GoldCoins * getinstance();
	CC_SYNTHESIZE_READONLY_PASS_BY_REF(Vector<BaseGoleCoin *>,golecoinVector,GolecoinVector);
	void addgolecoin(BaseGoleCoin * bc);
	void deletegolecoin();

};
#endif
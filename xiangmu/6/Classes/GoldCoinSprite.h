#ifndef __GOLDCOINSPRITE_H_
#define __GOLDCOINSPRITE_H_
#include "cocos2d.h"
#include "BaseGoldCoin.h"
class GoldCoinSprite:public BaseGoleCoin{
protected:
	int score;
	int coin;
public:
	virtual bool init(std::string fileName,int r_id_x,int r_id_y);
	static GoldCoinSprite * create(std::string fileName,int r_id_x,int r_id_y);
};
#endif
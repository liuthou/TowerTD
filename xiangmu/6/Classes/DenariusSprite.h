#ifndef __DENARIUSSPRITE_H_
#define __DENARIUSSPRITE_H_
#include "cocos2d.h"
#include "BaseGoldCoin.h"
class DenariusSprite:public BaseGoleCoin{
protected:
	int score;
	int coin;
public:
	virtual bool init(std::string fileName,int r_id_x,int r_id_y);
	static DenariusSprite * create(std::string fileName,int r_id_x,int r_id_y);
};
#endif
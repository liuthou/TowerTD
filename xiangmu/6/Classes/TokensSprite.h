#ifndef __TOKENSSPRITE_H_
#define __TOKENSSPRITE_H_
#include "cocos2d.h"
#include "BaseGoldCoin.h"
using namespace cocos2d;
class TokensSprite:public BaseGoleCoin{
private:
	int score;
	int coin;
public:
	virtual bool init(std::string fileName,int r_id_x,int r_id_y);
	static TokensSprite * create(std::string fileName,int r_id_x,int r_id_y);
};
#endif
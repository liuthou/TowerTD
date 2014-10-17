#include "GoldCoinSprite.h"

bool GoldCoinSprite::init(std::string fileName,int r_id_x,int r_id_y){
	if (!BaseGoleCoin::init(fileName,r_id_x,r_id_y)){
		return false;
	}
	score = 1000;
	coin = 1000;
	return true;		
}
GoldCoinSprite * GoldCoinSprite::create(std::string fileName,int r_id_x,int r_id_y){
	GoldCoinSprite * gc = new GoldCoinSprite();
	if (gc && gc->init(fileName,r_id_x,r_id_y)){
		gc->autorelease();
		return gc;
	}
	CC_SAFE_DELETE(gc);
	return nullptr;
}
#include "DenariusSprite.h"
bool DenariusSprite::init(std::string fileName,int r_id_x,int r_id_y){
	if (!BaseGoleCoin::init(fileName,r_id_x,r_id_y)){
		return false;
	}
	score = 300;
	coin = 100;
	return true;
}
DenariusSprite * DenariusSprite::create(std::string fileName,int r_id_x,int r_id_y){
	DenariusSprite * ds = new DenariusSprite();
	if (ds && ds->init(fileName,r_id_x,r_id_y)){
		ds->autorelease();
		return ds;
	}
	CC_SAFE_DELETE(ds);
	return nullptr;
}
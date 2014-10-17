#include "RedGemstone.h"
bool RedGemstone::init(std::string fileName,int r_id_x,int r_id_y){
	if (!BaseGemstone::init(fileName,r_id_x,r_id_y)){
		return false;
	}
	score = 1500;
	coin = 2000;
	return true;
}
RedGemstone * RedGemstone::create(std::string fileName,int r_id_x,int r_id_y){
	RedGemstone * rg = new RedGemstone();
	if (rg && rg->init(fileName,r_id_x,r_id_y)){
		rg->autorelease();
		return rg;
	}
	CC_SAFE_DELETE(rg);
	return nullptr;
}
std::string RedGemstone::sendCast(){
    return NOTIFICATIONCENTER_ROLE_JUMP_FOR_TOOLS_TYPE;
}
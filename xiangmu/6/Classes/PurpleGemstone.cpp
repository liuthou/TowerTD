#include "PurpleGemstone.h"
bool PurpleGemstone::init(std::string fileName,int r_id_x,int r_id_y){
	if (!BaseGemstone::init(fileName,r_id_x,r_id_y)){
		return false;
	}
	score = 5000;
	coin = 5000;
	return true;
}
PurpleGemstone * PurpleGemstone::create(std::string fileName,int r_id_x,int r_id_y){
	PurpleGemstone * pg = new PurpleGemstone();
	if (pg && pg->init(fileName,r_id_x,r_id_y)){
		pg->autorelease();
		return pg;
	}
	CC_SAFE_DELETE(pg);
	return nullptr;
}
std::string PurpleGemstone::sendCast(){
    return NOTIFICATIONCENTER_ROLE_JUMP_FOR_TOOLS_TYPE;
}
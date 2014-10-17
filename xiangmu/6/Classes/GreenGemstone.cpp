#include "GreenGemstone.h"
#include "HitBodys.h"
bool GreenGemstone::init(std::string fileName,int r_id_x,int r_id_y){
	if (!BaseGemstone::init(fileName,r_id_x,r_id_y)){
		return false;
	}
	score = 10000;
	coin = 8000;
    HitBodys::getInstance()->addToolsScrpit(this);
	return true;
}
GreenGemstone * GreenGemstone::create(std::string fileName,int r_id_x,int r_id_y){
	GreenGemstone * gg = new GreenGemstone();
	if (gg && gg->init(fileName,r_id_x,r_id_y)){
		gg->autorelease();
		return gg;
	}
	CC_SAFE_DELETE(gg);
	return nullptr;
}
std::string GreenGemstone::sendCast(){
    return NOTIFICATIONCENTER_ROLE_JUMP_FOR_TOOLS_TYPE;
}
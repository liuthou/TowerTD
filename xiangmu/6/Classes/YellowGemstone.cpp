#include "YellowGemstone.h"
bool YellowGemstone::init(std::string fileName, int r_id_x, int r_id_y){
	if (!BaseGemstone::init(fileName, r_id_x, r_id_y)){
		return false;
	}
	score = 1000;
	coin = 500;
	return false;
}
YellowGemstone * YellowGemstone::create(std::string fileName, int r_id_x, int r_id_y){
	YellowGemstone * yg = new YellowGemstone();
	if (yg && yg->init(fileName, r_id_x, r_id_y)){
		yg->autorelease();
		return yg;
	}
	CC_SAFE_DELETE(yg);
	return nullptr;
}
std::string YellowGemstone::sendCast(){
    return NOTIFICATIONCENTER_ROLE_JUMP_FOR_TOOLS_TYPE;
}
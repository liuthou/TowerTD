#include "WhiteGemstone.h"
bool WhiteGemstone::init(std::string fileName,int r_id_x,int r_id_y){
	if (!BaseGemstone::init(fileName,r_id_x,r_id_y)){
		return false;
        
	}
	score = 2000;
	coin = 3000;
	return true;
}
std::string WhiteGemstone::sendCast(){
    return NOTIFICATIONCENTER_ROLE_JUMP_FOR_TOOLS_TYPE;
}
WhiteGemstone * WhiteGemstone::create(std::string fileName,int r_id_x,int r_id_y){
	WhiteGemstone * wg = new WhiteGemstone();
	if (wg && wg->init(fileName,r_id_x,r_id_y)){
		wg->autorelease();
		return wg;
	}
	CC_SAFE_DELETE(wg);
	return nullptr;
}

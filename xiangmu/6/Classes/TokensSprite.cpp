#include "TokensSprite.h"
bool TokensSprite::init(std::string fileName,int r_id_x,int r_id_y){
	if (!BaseGoleCoin::init(fileName,r_id_x,r_id_y)){
		return false;
	}
	score = 100;
	coin = 10;
	return true;
}
TokensSprite * TokensSprite::create(std::string fileName,int r_id_x,int r_id_y){
	TokensSprite * tk = new TokensSprite();
	if (tk && tk->init(fileName,r_id_x,r_id_y)){
		tk->autorelease();
		return tk;
	}
	CC_SAFE_DELETE(tk);
	return nullptr;
}
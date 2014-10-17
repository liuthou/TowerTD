#include "TokenRect.h"

bool TokenRect::init(std::string fileName){
	if (!BaseRewards::initWithFile(fileName)){
		return false;
	}
	return true;
}

void TokenRect::onEnter(){
	BaseRewards::onEnter();
	addCoinAnimation();
}

void TokenRect::addCoinAnimation(){
	auto leftRote = RotateBy::create(1, Vec3(0,40,0));
	auto rightRote = RotateBy::create(1, Vec3(0,-40,0));
	auto linkLeftRight = Sequence::create(leftRote, rightRote, NULL);
	this->runAction(RepeatForever::create(linkLeftRight));
}

TokenRect * TokenRect::create(std::string fileName){
	TokenRect * tr = new TokenRect();
	if (tr && tr->init(fileName)){
		tr->autorelease();
		return tr;
	} 
	CC_SAFE_DELETE(tr);
	return nullptr;
}
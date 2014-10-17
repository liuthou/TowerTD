#include "BaseBullet.h"

bool BaseBullet::init(std::string fileName){
	if (!Sprite::initWithSpriteFrameName(fileName))
	{
		return false;
	}
	m_vsize = Director::getInstance()->getVisibleSize();

	m_range = 250;		//   Éä³Ì

	m_state = false;

	

	return true;
}

	
BaseBullet * BaseBullet::create(std::string fileName){
	BaseBullet * basebullet = new BaseBullet();
	if(basebullet && basebullet->init(fileName)){
		basebullet->autorelease();
		return basebullet;
	}
	CC_SAFE_DELETE(basebullet);
	return nullptr;
}

void BaseBullet::die(){			// ËÀÍö
	this->removeFromParentAndCleanup(true);
	this->setState(true);
}

void BaseBullet::move(){		//   ÒÆ¶¯

}

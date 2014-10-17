#include "BaseSprite.h"

bool BaseSprite::init(std::string fileName){
	if (!Sprite::initWithSpriteFrameName(fileName))
	{
		return false;
	}

	return true;
}
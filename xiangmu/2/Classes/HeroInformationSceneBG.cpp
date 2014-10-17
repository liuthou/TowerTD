
#include "VisibileSize.h"
#include "HeroInformationSceneBG.h"

bool HeroInformationSceneBG::init(){
	if (!Layer::init()) {
		return false;
	}

	//hero information background
	auto backGround = Sprite::create("ChangeAttackBG.png");
	//Ëõ·Å´óÐ¡
	float bgX = vSize.width / backGround->getContentSize().width;
	float bgY = vSize.height / backGround->getContentSize().height;
	backGround->setScale(bgX, bgY);
	backGround->setPosition(vSize / 2);
	addChild(backGround);


	return true;
}
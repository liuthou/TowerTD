
#include "ChangeAttackBGLayer.h"
#include "VisibileSize.h"
#include "VectorItemImage.h"

bool ChangeAttackBGLayer::init(){
	if (!Layer::init()) {
		return false;
	}

	addBackground();
	addReturnMenu();



	return true;
}

void ChangeAttackBGLayer::addBackground(){
	auto backGround = Sprite::create("ChangeAttackBG.png");
	//缩放大小
	float bgX = vSize.width / backGround->getContentSize().width;
	float bgY = vSize.height / backGround->getContentSize().height;
	backGround->setScale(bgX, bgY);
	backGround->setPosition(vSize / 2);
	addChild(backGround);


}

void ChangeAttackBGLayer::addReturnMenu(){
	//插入返回按钮
	auto menuitemLast = MenuItemImage::create("backbt.png", "backbtn-disable.png", CC_CALLBACK_1(ChangeAttackBGLayer::returnLast, this));
	auto menuLast = Menu::create(menuitemLast, NULL);
	menuLast->setPosition(Vec2(vSize.width / 12, vSize.height - menuitemLast->getContentSize().height / 2));
	log("menuLast = %f", menuLast->getPositionY());
	addChild(menuLast);

}


void ChangeAttackBGLayer::returnLast(Ref * sender){
	VectorItemImage::getInstance()->reset();
	Director::getInstance()->popScene();
}

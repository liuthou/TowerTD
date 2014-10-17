//
//  ChooseToolsLayer.cpp
//  heroJump
//
//  Created by mazhai on 14-9-23.
//
//

#include "ChooseToolsLayer.h"
#include "JumpHelp.h"

bool ChooseToolsLayer::init(){
    if(!Layer::init()){
        return false;
    }
	_bIsChooseTool = false;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tools/tools.plist");
	Sprite * boxSprite1 = Sprite::createWithSpriteFrameName ("NO-10017.png");
	boxSprite1->setPosition(Vec2(80,50));
	boxSprite1->setScale(1.2);
	this->addChild(boxSprite1);
	Sprite * boxSprite2 = Sprite::createWithSpriteFrameName ("NO-10017.png");
	boxSprite2->setPosition(boxSprite1->getPositionX() + 100, boxSprite1->getPositionY());
	boxSprite2->setScale(1.2);
	this->addChild(boxSprite2);
	sp_item = MenuItemSprite::create(Sprite::createWithSpriteFrameName("strap.png"),Sprite::createWithSpriteFrameName("strap.png"),CC_CALLBACK_1(ChooseToolsLayer::strengthenBright,this));
	sp_item->setScale(0.5,3);
	sp_item->setOpacity(OPACITY_NOMAL);
	sp_item->setTag(NOW_USE_TYPE::USE_RUBBERBAND);
	itemVector.push_back(sp_item);
	sp_menu = Menu::create(sp_item,NULL);
	Vec2 strap_pos = boxSprite2->getPosition();
	sp_menu->setPosition(strap_pos.x, strap_pos.y);
	this->addChild(sp_menu,1,100);
	mood_item = MenuItemSprite::create(Sprite::create("tools/mood3.png"),Sprite::create("tools/mood3.png"),CC_CALLBACK_1(ChooseToolsLayer::strengthenBright,this));
	mood_item->setScale(0.5,1.5);
	mood_item->setOpacity(OPACITY_HIGHT);
	mood_item->setTag(NOW_USE_TYPE::USE_WOOD);
	itemVector.push_back(mood_item);
	mood_menu = Menu::create(mood_item,NULL);
	Vec2 mood_pos = boxSprite1->getPosition();
	mood_menu->setPosition(mood_pos.x, mood_pos.y);
	this->addChild(mood_menu,1,101);
	selectMenuItem = NOW_USE_TYPE::USE_WOOD;
    mSkillButton = SkillButton::createSkillButton(10.f, "stencil.png", "normal.png");
    mSkillButton->setPosition(Vec2(getContentSize().width - mSkillButton -> getContentSize().width/2,mSkillButton -> getContentSize().height/2));
    this -> addChild(mSkillButton);
    mSkillButton -> startCd(100);
    return true;
}
NOW_USE_TYPE ChooseToolsLayer::getNowMenuItem(){
	return selectMenuItem;
}
void ChooseToolsLayer::strengthenBright(Ref * sender)
{
	auto menu = dynamic_cast<MenuItemSprite *> (sender);
	int index_ = NOW_USE_TYPE::USE_WOOD;
	int nowTag = menu->getTag();
	for (auto ite = itemVector.begin();ite != itemVector.end() ; ite++ )
	{
		if (index_ == nowTag )
		{
			selectMenuItem = (NOW_USE_TYPE)nowTag;
			(*ite) -> setOpacity(OPACITY_NOMAL);
		} else {
			(*ite) -> setOpacity(OPACITY_HIGHT);
		}
		index_++;
	}
    JumpHelp::getToolsLayer() -> setNowType(selectMenuItem);
}

void ChooseToolsLayer::addUseToolsBaseSprite(UseToolsBaseSprite* utbs)
{

}
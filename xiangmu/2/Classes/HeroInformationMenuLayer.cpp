
#include "VisibileSize.h"
#include "HeroInformationMenuLayer.h"

bool HeroInformationMenuLayer::init(){
	if (!Layer::init()) {
		return false;
	}

	//    addMenu();
	addCharacter();
	addIllustratedHandbook();
	addSkill();
	addMenu();

	return true;
}

void HeroInformationMenuLayer::addCharacter(){
	character = Sprite::create("HeroChangeWindow.png");
	character->setRotation(90);
	character->setPosition(vSize / 2);
	character->setScaleX(vSize.height / character->getContentSize().width);
	character->setVisible(false);
	addChild(character);
}

void HeroInformationMenuLayer::addIllustratedHandbook(){
	auto hiItem_a = MenuItemImage::create("SF_Card.png", "SF_Card.png");
	hiItem_a->setScale(vSize.height / hiItem_a->getContentSize().width / 2);
	auto hiItem_b = MenuItemImage::create("SF_Card.png", "SF_Card.png");
	auto hiToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HeroInformationMenuLayer::fieldGuideInformati, this), hiItem_a, hiItem_b, NULL);
	illustratedHhandbook = Menu::create(hiToggle, NULL);
	illustratedHhandbook->setPosition(vSize / 2);
	illustratedHhandbook->setVisible(false);
	addChild(illustratedHhandbook);

}

void HeroInformationMenuLayer::addSkill(){
	skill = Sprite::create("HeroChangeWindow.png");
	skill->setRotation(90);
	skill->setPosition(vSize / 2);
	skill->setScaleX(vSize.height / skill->getContentSize().width);
	skill->setVisible(false);
	addChild(skill);
}

//属性,图鉴,技能 开关
void HeroInformationMenuLayer::toggleButton(Ref * sender){
	MenuItemToggle * t = (MenuItemToggle *)sender;
	if (t->getName() == "character") {
		if (t->getSelectedIndex() == 1 && illustratedHhandbookToggle->getSelectedIndex() == 0 && skillToggle->getSelectedIndex() == 0) {

			auto characterMove = MoveBy::create(0.5, Vec2(-vSize.width / 4.8, 0));
			character->setVisible(true);
			character->runAction(characterMove);
			auto menuMove = MoveBy::create(0.5, Vec2(vSize.width / 5, 0));
			menuBG->runAction(menuMove);

		}
		if (t->getSelectedIndex() == 1 && (illustratedHhandbookToggle->getSelectedIndex() == 1 || skillToggle->getSelectedIndex() == 1)) {

			if (illustratedHhandbookToggle->getSelectedIndex() == 1) {
				illustratedHhandbookToggle->setSelectedIndex(0);
				auto illustratedHhandebookMove = MoveBy::create(0.5, Vec2(vSize.width / 5, 0));
				auto callVisibile = CallFunc::create([=](){
					illustratedHhandbook->setVisible(false);
				});
				auto seqAction = Sequence::create(illustratedHhandebookMove, callVisibile, NULL);
				illustratedHhandbook->runAction(seqAction);
				auto characterMove = MoveBy::create(0.5, Vec2(-vSize.width / 4.8, 0));
				character->setVisible(true);
				character->runAction(characterMove);

			}
			if (skillToggle->getSelectedIndex() == 1) {
				skillToggle->setSelectedIndex(0);
				auto skillMove = MoveBy::create(0.5, Vec2(vSize.width / 4.8, 0));
				auto callVisibile = CallFunc::create([=](){
					skill->setVisible(false);
				});
				auto seqAction = Sequence::create(skillMove, callVisibile, NULL);
				skill->runAction(seqAction);
				auto characterMove = MoveBy::create(0.5, Vec2(-vSize.width / 4.8, 0));
				character->setVisible(true);
				character->runAction(characterMove);
			}

		}
		if (t->getSelectedIndex() == 0) {
			auto characterMove = MoveBy::create(0.5, Vec2(vSize.width / 4.8, 0));
			auto callVisibile = CallFunc::create([=](){
				character->setVisible(false);
			});
			auto seqAction = Sequence::create(characterMove, callVisibile, NULL);
			character->runAction(seqAction);
			auto menuMove = MoveBy::create(0.5, Vec2(-vSize.width / 5, 0));
			menuBG->runAction(menuMove);
		}
	}

	if (t->getName() == "illustratedHhandbook") {
		if (t->getSelectedIndex() == 1 && characterToggle->getSelectedIndex() == 0 && skillToggle->getSelectedIndex() == 0) {

			auto illustratedMove = MoveBy::create(0.5, Vec2(-vSize.width / 5, 0));
			illustratedHhandbook->setVisible(true);
			illustratedHhandbook->runAction(illustratedMove);
			auto menuMove = MoveBy::create(0.5, Vec2(vSize.width / 5, 0));
			menuBG->runAction(menuMove);

		}
		if (t->getSelectedIndex() == 1 && (characterToggle->getSelectedIndex() == 1 || skillToggle->getSelectedIndex() == 1)) {

			if (characterToggle->getSelectedIndex() == 1) {
				characterToggle->setSelectedIndex(0);
				auto characterMove = MoveBy::create(0.5, Vec2(vSize.width / 4.8, 0));
				auto callVisibile = CallFunc::create([=](){
					character->setVisible(false);
				});
				auto seqAction = Sequence::create(characterMove, callVisibile, NULL);
				character->runAction(seqAction);
				auto illustratedMove = MoveBy::create(0.5, Vec2(-vSize.width / 5, 0));
				illustratedHhandbook->setVisible(true);
				illustratedHhandbook->runAction(illustratedMove);

			}
			if (skillToggle->getSelectedIndex() == 1) {
				skillToggle->setSelectedIndex(0);
				auto skillMove = MoveBy::create(0.5, Vec2(vSize.width / 4.8, 0));
				auto callVisibile = CallFunc::create([=](){
					skill->setVisible(false);
				});
				auto seqAction = Sequence::create(skillMove, callVisibile, NULL);
				skill->runAction(seqAction);
				auto illustratedMove = MoveBy::create(0.5, Vec2(-vSize.width / 5, 0));
				illustratedHhandbook->setVisible(true);
				illustratedHhandbook->runAction(illustratedMove);
			}

		}
		if (t->getSelectedIndex() == 0) {
			auto illustratedMove = MoveBy::create(0.5, Vec2(vSize.width / 5, 0));
			auto callVisibile = CallFunc::create([=](){
				illustratedHhandbook->setVisible(false);
			});
			auto seqAction = Sequence::create(illustratedMove, callVisibile, NULL);
			illustratedHhandbook->runAction(seqAction);
			auto menuMove = MoveBy::create(0.5, Vec2(-vSize.width / 5, 0));
			menuBG->runAction(menuMove);
		}
	}

	if (t->getName() == "skill") {
		if (t->getSelectedIndex() == 1 && characterToggle->getSelectedIndex() == 0 && illustratedHhandbookToggle->getSelectedIndex() == 0) {

			auto skillMove = MoveBy::create(0.5, Vec2(-vSize.width / 4.8, 0));
			skill->setVisible(true);
			skill->runAction(skillMove);
			auto menuMove = MoveBy::create(0.5, Vec2(vSize.width / 5, 0));
			menuBG->runAction(menuMove);

		}
		if (t->getSelectedIndex() == 1 && (characterToggle->getSelectedIndex() == 1 || illustratedHhandbookToggle->getSelectedIndex() == 1)) {

			if (characterToggle->getSelectedIndex() == 1) {
				characterToggle->setSelectedIndex(0);
				auto characterMove = MoveBy::create(0.5, Vec2(vSize.width / 4.8, 0));
				auto callVisibile = CallFunc::create([=](){
					character->setVisible(false);
				});
				auto seqAction = Sequence::create(characterMove, callVisibile, NULL);
				character->runAction(seqAction);
				auto skillMove = MoveBy::create(0.5, Vec2(-vSize.width / 4.8, 0));
				skill->setVisible(true);
				skill->runAction(skillMove);

			}
			if (illustratedHhandbookToggle->getSelectedIndex() == 1) {
				illustratedHhandbookToggle->setSelectedIndex(0);
				auto illustratedMove = MoveBy::create(0.5, Vec2(vSize.width / 5, 0));
				auto callVisibile = CallFunc::create([=](){
					illustratedHhandbook->setVisible(false);
				});
				auto seqAction = Sequence::create(illustratedMove, callVisibile, NULL);
				illustratedHhandbook->runAction(seqAction);
				auto skillMove = MoveBy::create(0.5, Vec2(-vSize.width / 4.8, 0));
				skill->setVisible(true);
				skill->runAction(skillMove);
			}

		}
		if (t->getSelectedIndex() == 0) {
			auto skillMove = MoveBy::create(0.5, Vec2(vSize.width / 4.8, 0));
			auto callVisibile = CallFunc::create([=](){
				skill->setVisible(false);
			});
			auto seqAction = Sequence::create(skillMove, callVisibile, NULL);
			skill->runAction(seqAction);
			auto menuMove = MoveBy::create(0.5, Vec2(-vSize.width / 5, 0));
			menuBG->runAction(menuMove);
		}
	}



}

//图鉴内容开关
void HeroInformationMenuLayer::fieldGuideInformati(Ref *sender){
	MenuItemToggle * t = (MenuItemToggle *)sender;
	if (t->getSelectedIndex() == 1) {
		t->setEnabled(false);
		illustratedHhandbook->setZOrder(100);
		auto fieldImage = t->getSubItems().at(0);
		auto fieldGuideMove = MoveBy::create(0.5, Vec2(vSize.width / 5, 0));
		auto fieldGuideRotation = RotateBy::create(0.5, -90);
		auto fieldGuideScale = ScaleBy::create(0.5, vSize.width / (fieldImage->getContentSize().width * 2));
		auto fieldGuideCall = CallFunc::create([=](){
			t->setEnabled(true);
		});
		auto seqAction = Spawn::create(fieldGuideMove, fieldGuideRotation, fieldGuideScale, NULL);
		auto sequenceAC = Sequence::create(seqAction, fieldGuideCall, NULL);
		t->runAction(sequenceAC);
	}
	if (t->getSelectedIndex() == 0) {
		t->setEnabled(false);
		auto fieldImage = t->getSubItems().at(0);
		float scale = vSize.width / (fieldImage->getContentSize().width * 2);
		auto fieldGuideMove = MoveBy::create(0.5, Vec2(-vSize.width / 5, 0));
		auto fieldGuideRotation = RotateBy::create(0.5, 90);
		auto fieldGuideScale = ScaleBy::create(0.5, fieldImage->getContentSize().width / (fieldImage->getContentSize().width * scale));
		auto spaAction = Spawn::create(fieldGuideMove, fieldGuideRotation, fieldGuideScale, NULL);
		auto callAction = CallFunc::create([=](){
			illustratedHhandbook->setZOrder(0);
			t->setEnabled(true);
		});
		auto seqAction = Sequence::create(spaAction, callAction, NULL);
		t->runAction(seqAction);
	}


}


void HeroInformationMenuLayer::Return(Ref * sender){

	Director::getInstance()->popScene();

}

void HeroInformationMenuLayer::addMenu(){

	menuBG = Sprite::create("HeroChangeWindow.png");
	menuBG->setPosition(vSize / 2);
	//图片缩放比例
	float flexibleX = vSize.width / 2 / menuBG->getContentSize().width;
	float flexibleY = vSize.height / menuBG->getContentSize().height;
	menuBG->setScale(flexibleX, flexibleY);
	this->addChild(menuBG, 1);

	log("%f %f", flexibleY, flexibleX);
	//退出按钮
	auto returnItem = MenuItemImage::create("common_tips_button_close_.png", "common_tips_button_close_.png", CC_CALLBACK_1(HeroInformationMenuLayer::Return, this));
	//    returnItem->setScale(2 - flexibleX ,2 - flexibleY);
	auto returnMenu = Menu::create(returnItem, NULL);
	float rmX = menuBG->getContentSize().width;
	float rmY = menuBG->getContentSize().height - returnItem->getContentSize().height / 2;
	returnMenu->setPosition(Vec2(rmX, rmY));
	menuBG->addChild(returnMenu);
	log("%f,%f", rmX, menuBG->getContentSize().height / 2);
	//三个开关的实现
	//属性
	auto characterItem_a = MenuItemImage::create("ShuXing_a.png", "ShuXing_a.png");
	auto characterItem_b = MenuItemImage::create("ShuXing_b.png", "ShuXing_b.png");
	characterToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HeroInformationMenuLayer::toggleButton, this), characterItem_a, characterItem_b, NULL);
	characterToggle->setName("character");

	//图鉴
	auto illustratedHhandbook_a = MenuItemImage::create("TuJian_a.png", "TuJian_a.png");
	auto illustratedHhandbook_b = MenuItemImage::create("TuJian_b.png", "TuJian_b.png");
	illustratedHhandbookToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HeroInformationMenuLayer::toggleButton, this), illustratedHhandbook_a, illustratedHhandbook_b, NULL);
	illustratedHhandbookToggle->setName("illustratedHhandbook");

	//技能
	auto skill_a = MenuItemImage::create("JiNeng_a.png", "JiNeng_a.png");
	auto skill_b = MenuItemImage::create("JiNeng_b.png", "JiNeng_b.png");
	skillToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HeroInformationMenuLayer::toggleButton, this), skill_a, skill_b, NULL);
	skillToggle->setName("skill");

	//把三个开关放到菜单中
	auto toggleMenu = Menu::create(characterToggle, illustratedHhandbookToggle, skillToggle, NULL);
	float tmX = menuBG->getContentSize().width / 2;
	float tmY = characterItem_a->getContentSize().height / 1.5;
	toggleMenu->setPosition(Vec2(tmX, tmY));
	toggleMenu->alignItemsHorizontally();
	menuBG->addChild(toggleMenu);

	//加入主角图片
	auto role = Sprite::create("SF_Image.png");
	float rX = role->getContentSize().width / 1.5;
	float rY = menuBG->getContentSize().height - (role->getContentSize().height / 2);
	role->setPosition(Vec2(rX, rY));
	menuBG->addChild(role);

}
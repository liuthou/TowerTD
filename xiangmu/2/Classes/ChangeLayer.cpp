
#include "ChangeLayer.h"
#include "VectorItemImage.h"
#include "GameAttackScene.h"
#include "ChangeAttackBGLayer.h"
#include "VisibileSize.h"
#include "choseInformation.h"
#include "LevelScene.h"
bool ChangeLayer::init(){
	if (!Layer::init()) {
		return false;
	}
	bgX = Director::getInstance()->getVisibleSize().width;
	bgY = Director::getInstance()->getVisibleSize().height;
	auto backGround = ChangeAttackBGLayer::create();
	addChild(backGround);

	allowChangeHero();
	//英雄选择之后的窗口
	decisionWindow = Sprite::create("HeroDecisionWindow.png");
	decisionWindow->setPosition(Vec2(vSize.width / 2, vSize.height * 0.29 / 2));
	addChild(decisionWindow);

	auto changeOverItem = MenuItemImage::create("Attack_a.png", "Attack_b.png", CC_CALLBACK_1(ChangeLayer::changeOver, this));
	auto changeOverMenu = Menu::create(changeOverItem, NULL);
	float comX = decisionWindow->getPosition().x + changeOverItem->getContentSize().width * 3;
	float comY = decisionWindow->getPosition().y;
	changeOverMenu->setPosition(Vec2(comX, comY));
	addChild(changeOverMenu, 2000);


	return true;
}

//创建英雄选择菜单界面
void ChangeLayer::allowChangeHero(){

	//英雄选择窗口
	auto changeWindow = Sprite::create("HeroChangeWindow.png");
	changeWindow->setPosition(Vec2(vSize.width / 2, vSize.height - vSize.height * 0.625 / 2));
	changeWindow->setOpacity(150);
	changeWindow->setScale(1.5, 1);
	addChild(changeWindow);

	heromenu = Menu::create();
	float cx = changeWindow->getPosition().x - changeWindow->getContentSize().width / 2 * 1.5 + 20;
	float cy = changeWindow->getPosition().y + changeWindow->getContentSize().height / 2 - 20;
	heromenu->setPosition(Vec2(cx, cy));
	this->addChild(heromenu, 1001);


	//把英雄图像做成按钮
	auto heroImage1_a = MenuItemImage::create("POM.jpg", "POM.jpg");
	heroImage1_a->setTag(1001);
	auto heroImage1_b = MenuItemImage::create("POM.jpg", "POM.jpg");
	heroImage1_a->setName("Person.xml");
	heroImage1_b->setName("Person.xml");
	auto hero1 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(ChangeLayer::changeHeroItem, this), heroImage1_a, heroImage1_b, NULL);
	hero1->setPosition(Vec2(52, -52));
	hero1point = Vec2(52, -52);
	hero1->setTag(1001);
	heromenu->addChild(hero1);
	//创建底部灰色的图片
	auto selecteHero1 = Sprite::create("imagePOM.png");
	selecteHero1->setPosition(heroImage1_a->convertToWorldSpace(heroImage1_a->getPosition()));
	addChild(selecteHero1, 1000);


	auto heroImage2_a = MenuItemImage::create("Pugna.jpg", "Pugna.jpg");
	auto heroImage2_b = MenuItemImage::create("Pugna.jpg", "Pugna.jpg");
	heroImage2_a->setName("Person.xml");
	heroImage2_b->setName("Person.xml");
	auto hero2 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(ChangeLayer::changeHeroItem, this), heroImage2_a, heroImage2_b, NULL);
	hero2->setPosition(Vec2(186, -52));
	hero2point = Vec2(186, -52);
	hero2->setTag(1002);
	heromenu->addChild(hero2);
	auto selecteHero2 = Sprite::create("imagePugna.png");
	selecteHero2->setPosition(heroImage2_a->convertToWorldSpace(heroImage2_a->getPosition()));
	addChild(selecteHero2, 1000);

	auto heroImage3_a = MenuItemImage::create("SF.jpg", "SF.jpg");
	auto heroImage3_b = MenuItemImage::create("SF.jpg", "SF.jpg");
	heroImage3_a->setName("Person.xml");
	heroImage3_b->setName("Person.xml");
	auto hero3 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(ChangeLayer::changeHeroItem, this), heroImage3_a, heroImage3_b, NULL);
	hero3->setPosition(Vec2(320, -52));
	hero3point = Vec2(320, -52);
	hero3->setTag(1003);
	heromenu->addChild(hero3);
	auto selecteHero3 = Sprite::create("imageSF.png");
	selecteHero3->setPosition(heroImage3_a->convertToWorldSpace(heroImage3_a->getPosition()));
	addChild(selecteHero3, 1000);





}

void ChangeLayer::changeHeroItem(Ref * sender){
	MenuItemToggle * t = (MenuItemToggle *)sender;


	//判断开关状态
	if (t->getSelectedIndex() == 1) {
		menuItemToggle.pushBack(t);
		VectorItemImage::getInstance()->addVectorItemImage((MenuItemImage *)t->getSubItems().at(0));
		//决定其下行的位置
		point = Vec2((menuItemToggle.size() - 1) * 134 + 62, -504);
		t->runAction(MoveTo::create(0.5, point));

	}

	if (t->getSelectedIndex() == 0) {


		if (t->getTag() == 1001) {
			menuItemToggle.eraseObject(t);
			VectorItemImage::getInstance()->deleteVectorItemImage((MenuItemImage *)t->getSubItems().at(0));
			auto call = CallFunc::create([=](){
				for (int i = 0; i < menuItemToggle.size(); i++) {
					auto toggle = menuItemToggle.at(i);
					toggle->setPosition(Vec2(62 + 134 * i, -504));
				}
			});
			auto seq = Sequence::create(MoveTo::create(1, hero1point), call, NULL);
			t->runAction(seq);
		}

		if (t->getTag() == 1002) {
			menuItemToggle.eraseObject(t);
			VectorItemImage::getInstance()->deleteVectorItemImage((MenuItemImage *)t->getSubItems().at(0));
			auto call = CallFunc::create([=](){
				for (int i = 0; i < menuItemToggle.size(); i++) {
					auto toggle = menuItemToggle.at(i);
					toggle->setPosition(Vec2(62 + 134 * i, -504));

				}
			});
			auto seq = Sequence::create(MoveTo::create(1, hero2point), call, NULL);
			t->runAction(seq);
		}

		if (t->getTag() == 1003) {
			menuItemToggle.eraseObject(t);
			VectorItemImage::getInstance()->deleteVectorItemImage((MenuItemImage *)t->getSubItems().at(0));
			auto call = CallFunc::create([=](){
				for (int i = 0; i < menuItemToggle.size(); i++) {
					auto toggle = menuItemToggle.at(i);
					toggle->setPosition(Vec2(62 + 134 * i, -504));

				}
			});
			auto seq = Sequence::create(MoveTo::create(1, hero3point), call, NULL);
			t->runAction(seq);
		}


	}

	if (menuItemImage.size() > 4)//如果已经选择了五个英雄
	{
		for (int i = 0; i < menuItemToggle.size(); i++)
		{

			menuItemToggle.at(i)->setEnabled(false);
		}
	}



}

void ChangeLayer::changeOver(Ref * sender){
	if (menuItemToggle.size() == 0) {
		return;
	}
	auto scene = GameAttackScene::create();
	Director::getInstance()->replaceScene(scene);

}
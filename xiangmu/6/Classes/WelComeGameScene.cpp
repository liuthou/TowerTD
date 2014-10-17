

//
//  WelComeGameScene.cpp
//  heroJump
//
//  Created by mazhai on 14-9-16.
//
//


//
//  WelComeGameScene.cpp
//  heroJump
//
//  Created by mazhai on 14-9-16.
//
//

#include "WelComeGameScene.h"



#include "WelComeGameScene.h"
#include "Sov.h"
#include "SelectGameScene.h"
#include "BaseRewards.h"
#include "BackgroundLayer.h"
#include "ConfigUtil.h"
#include "AudioUtil.h"

Scene* WelComeGameScene::createScene(){
    auto scene = Scene::create();
    auto layer = WelComeGameScene::create();
    scene->addChild(layer);
    return scene;
}
bool WelComeGameScene::init(){
    if (!Layer::init()) {
        return false;
    }

	//add background
	vSize = Director::getInstance()->getVisibleSize();
	bg = Sprite::create("bg9.jpg");
	bg->setScale(vSize.height/bg->getContentSize().height);
	bg->setPosition(vSize.width/2,vSize.height/2);
	this->addChild(bg);



    return true;
}
void WelComeGameScene::onEnter(){
	Layer::onEnter();
    AudioUtil::getInstance()->playBackgroundSound("StartBackGround.mp3");
    
	addLabel();
}

void WelComeGameScene::addLabel(){


	auto label1 = Label::createWithTTF(UTEXT("跳"),"fonts/8.ttf",180);
	auto label2 = Label::createWithTTF(UTEXT("尼"),"fonts/8.ttf",150);
	auto label3 = Label::createWithTTF(UTEXT("达"),"fonts/8.ttf",180);
	auto label4 = Label::createWithTTF("YeaH","fonts/6.ttf",150);


	label1->setPosition(vSize.width/6,vSize.height/2);//100,480
	label2->setPosition(vSize.width/2,vSize.height/2-30);//320,450
	label3->setPosition(vSize.width-70,vSize.height/2+20);//550,480
	label4->setPosition(vSize.width/2+80,vSize.height/2+170);//400,650



	auto lb1_1 = JumpBy::create(1,Vec2(0,0),150,2);
	auto lb1_2 = JumpBy::create(1,Vec2(0,100),50,2);
	label1->runAction(Sequence::create(lb1_1,lb1_2,NULL));

	auto lb2_1 = JumpBy::create(1,Vec2(0,100),0,0);
	auto lb2_2 = JumpBy::create(1,Vec2(0,100),50,2);
	label2->runAction(Sequence::create(lb2_1,lb2_2,NULL));

	auto lb3_1 = JumpBy::create(1,Vec2(0,100),0,0);
	auto lb3_2 = JumpBy::create(1,Vec2(0,100),50,2);
	label3->runAction(Sequence::create(lb3_1,lb3_2,NULL));

	auto lb4_1 = Blink::create(1,5);
	auto lb4_2 = MoveBy::create(1,Vec2(20,-350));
	auto lb4_3 = JumpBy::create(1,Vec2(0,100),50,2);
	auto lb4_4 = DelayTime::create(1);
	auto lb4_5 = CallFunc::create([=](void){
		Director::getInstance()->replaceScene(SelectGameScene::creatScene());
	});
	label4->runAction(Sequence::create(lb4_1,lb4_2,lb4_3,lb4_4,lb4_5,NULL));

	this->addChild(label1);
	this->addChild(label2);
	this->addChild(label3);
	this->addChild(label4);
	

}

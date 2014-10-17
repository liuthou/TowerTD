#include "ExcessiveScene.h"
#include "RoleAnimate.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;


bool ExcessiveScene::init(){
	if(!Scene::init()){
		return false;
	}
	Size vsize = Director::getInstance()->getVisibleSize();
	Sprite * bg = Sprite::create("bg17a.jpg");
	bg->setNormalizedPosition(Vec2(0.5,0.5));
	bg->setScaleY(1.2);
	this->addChild(bg);

	Sprite * sp = Sprite::createWithSpriteFrameName("heroStandRight_01.png");
	sp->setNormalizedPosition(Vec2(0.5,0.3));
	auto spani = RoleAnimate::getinstance()->createAmt("heroStandRight_0%d.png",4,0.2,2);
	auto jump = JumpBy::create(2,Vec2(0,vsize.height - sp->getPositionY()),vsize.height - sp->getPositionY(),1);
	auto cf = CCCallFunc::create([=](){
		
		GameScene * scene = GameScene::create();
		Director::getInstance()->replaceScene(scene);
	});
	auto cf1 = CCCallFunc::create([=](){
		SimpleAudioEngine::getInstance()->playEffect("tiaozhuan.wav");
	});
	auto spaw = Spawn::create(jump,cf1,NULL);
	auto seq = Sequence::create(spani,spaw,cf,NULL);
	sp->setScale(1.4);
	this->addChild(sp);
	sp->runAction(seq);
	
	return true;
}
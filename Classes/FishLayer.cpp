#include "FishLayer.h"
#include "GameBasic.h"

bool FishLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto bg = Sprite::create("mymap.png");
	this->addChild(bg);
	bg->setAnchorPoint(Vec2::ZERO);
	std::string fileName = "3D/gailun.c3b";
	_sprite = Sprite3D::create(fileName);
	_sprite->setScale(0.1f);
	auto s = Director::getInstance()->getVisibleSize();
	_sprite->setPosition(Vec2(s.width*2.f / 5.f, s.height / 2.f));
	this->addChild(_sprite);

	auto animation = Animation3D::create(fileName);
// 	if (animation)
// 	{
// 
// 		//start ~ 1.933s swim
// 		_swim = Animate3D::create(animation, 0.1f, 1.933f);
// 		_swim->retain();
// 
// 		//1.933s~2.8s hurt
// 		_hurt = Animate3D::create(animation, 1.933f, 2.8f);
// 		_hurt->retain();
// 
// 		// repeat to play
// 		Sequence* pSequence = Sequence::create(_swim, _hurt, NULL);
// 		_sprite->runAction(RepeatForever::create(pSequence));
// 	}
// 	
// 	ArmatureDataManager::getInstance()->addArmatureFileInfo("Test/Test.ExportJson");
// 
// 	auto amt = Armature::create("Test");
// 	amt->getAnimation()->play("DOWN");
// 	amt->setPosition(480, 320);	
// 	this->addChild(amt);
// 	auto amt1 = Armature::create("Test");
// 	amt1->getAnimation()->play("UP");
// 	amt1->setPosition(280, 320);
// 	this->addChild(amt1);
// 
// 	auto amt11 = Armature::create("Test");
// 	amt11->getAnimation()->play("LEFT");
// 	amt11->setPosition(180, 320);
// 	this->addChild(amt11);

	return true;
}
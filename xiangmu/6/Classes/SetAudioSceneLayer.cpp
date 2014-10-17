#include "SetAudioSceneLayer.h"
#include "AudioUtil.h"
Scene * SetAudioSceneLayer::createScene()
{
	Scene * s = Scene::create();
	SetAudioSceneLayer * l = SetAudioSceneLayer::create();
	s->addChild(l);
	return s;
}


bool SetAudioSceneLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("re.plist");
    Sprite * sprite_re = Sprite::create();
	sprite_re->setPosition(Vec2(400,800));
	this->addChild(sprite_re,11);
	auto animation = Animation::create();
	for (int i = 1; i < 5 ; i++)
	{
		__String * fileName = __String::createWithFormat("re%d.png",i);
		SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName->getCString());
		animation->addSpriteFrame(spriteFrame);
	}
	animation->setDelayPerUnit(0.5);
	animation->setLoops(-1);
	Animate * animate = Animate::create(animation);
	sprite_re->runAction(animate);

    auto star = ParticleSystemQuad::create("Start.plist");
    star->setPosition(320,480);
    this->addChild(star,2);
    
	return true;
}	

void SetAudioSceneLayer::onEnter()
{
	Layer::onEnter();
	menuItemPlayMusic();
}

//set play music menuToggle
void SetAudioSceneLayer::menuItemPlayMusic()
{
	Size viSize = Director::getInstance()->getVisibleSize();
	//add audio background
	Sprite * setAudioBackGround = Sprite::create("back.png");
	setAudioBackGround->setPosition(viSize.width/2, viSize.height/2);
	this->addChild(setAudioBackGround);

	//return setting page menuitem
	auto callBackItem = MenuItemImage::create("callBack.png", "callBack.png", CC_CALLBACK_1(SetAudioSceneLayer::onCallBack,this));
	callBackItem->setScale(0.5);
	//open play backgroundMusic item
	auto backGroundMusicOpenItem = MenuItemImage::create("BackGroundOpen.png", "BackGroundOpen.png");
	auto backGroundMusicCloseItem = MenuItemImage::create("BackGrounClose.png","BackGrounClose.png");

	//open play effect item
	auto effectMusitOpenItem = MenuItemImage::create("effectOpen.png","effectOpen.png");
	auto effectMusitCloseItem = MenuItemImage::create("effectClose.png","effectClose.png");

	//set bool play backGround music toggle
	auto itemBackGroundToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SetAudioSceneLayer::audioBackGroundMusic,this), backGroundMusicOpenItem, backGroundMusicCloseItem, NULL);

	//set bool play effect music toggle
	auto itemEffectToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SetAudioSceneLayer::audioEffectMusic,this), effectMusitOpenItem, effectMusitCloseItem, NULL);

	//set toggle picture size scale
	itemBackGroundToggle->setScale(2, 1.5);
	itemEffectToggle->setScale(2, 1.5);

	//backGroundToggle and effectToggle Menu
	Menu * menu1 = Menu::create(itemBackGroundToggle, itemEffectToggle, NULL);
	menu1->setPosition(Vec2(viSize.width - 100,viSize.height/2));
	menu1->alignItemsVerticallyWithPadding(20);
	this->addChild(menu1);

	//return setting page Menu
	Menu * menu2 = Menu::create(callBackItem,NULL);
	menu2->setPosition(menu1->getPositionX(), menu1->getPositionY() - 150);
	this->addChild(menu2);
}

//return setting page
void SetAudioSceneLayer::onCallBack(Ref * sender)
{
    Director::getInstance()->popScene();
}

void SetAudioSceneLayer::audioBackGroundMusic(Ref * sender)
{
	auto pAudioUtil = AudioUtil::getInstance();
	pAudioUtil->setIsBackGround(!pAudioUtil->getIsBackGround());
}

void SetAudioSceneLayer::audioEffectMusic(Ref * sender)
{
	auto pAudioUtil = AudioUtil::getInstance();
	pAudioUtil->setIsEffectPlay(!pAudioUtil->getIsEffectPlay());
}

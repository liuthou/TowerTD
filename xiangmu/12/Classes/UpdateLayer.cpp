#include "UpdateLayer.h"
#include "GameManager.h"
#include "BaseTower.h"

using namespace DrawPrimitives;

UpdateLayer*UpdateLayer::create(BaseTower *tower)
{
	auto updatePoint = new UpdateLayer();
	if(updatePoint && updatePoint->init(tower))
	{
		updatePoint->autorelease();
		return  updatePoint;
	}
	CC_SAFE_DELETE(updatePoint);  
	return nullptr;
}

bool UpdateLayer::init(BaseTower *tower)
{
	if(!Layer::init())
	{
		return false;
	}
	this->towers = tower;
	this->setTag(100);
    show();
	/*auto listen = EventListenerTouchOneByOne::create();
	listen->onTouchBegan=[=](Touch *t,Event *e){
	return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen,this);*/
    return  true;
}
    
void UpdateLayer::show()
{
	   
    //点击会进入到升级
     MenuItemImage * item1 = MenuItemImage::create("456.png","456.png",[=](Ref *){
		 if(towers->getCurlevel()<4){
              SimpleAudioEngine::getInstance()->playEffect("getgold.wav");
		 }
		 towers->postuplevel();
		  auto dt = CallFunc::create(CC_CALLBACK_0(UpdateLayer::unshow,this));
		  this->runAction( Sequence::createWithTwoActions(DelayTime::create(0.1f),dt));
	});
	 //升级标签
	 updateLabel= Label::createWithTTF("100","Marker Felt.ttf",30);
	 updateLabel->setColor(cocos2d::Color3B::YELLOW);
	 updateLabel->setScale(0.8f);
	 updateLabel->setAnchorPoint(Vec2( 0.5f,0.5f));
	 updateLabel->setPosition(Vec2(item1->getPosition()+Vec2(30,20)));
	 item1->addChild(updateLabel);

	MenuItemImage * item2 = MenuItemImage::create("delete.png","asd.png",[=](Ref *){

		SimpleAudioEngine::getInstance()->playEffect("arrowTower.wav");
		towers->postDeleteTower();
		auto dt = CallFunc::create(CC_CALLBACK_0(UpdateLayer::unshow,this));
		this->runAction( Sequence::createWithTwoActions(DelayTime::create(0.1f),dt));
	});
	//铲除标签
	auto eradicantLabel= Label::createWithTTF("200","Marker Felt.ttf",30);
	eradicantLabel->setColor(cocos2d::Color3B::YELLOW);
	eradicantLabel->setScale(0.8f);
	eradicantLabel->setAnchorPoint(Vec2(0,0));
	eradicantLabel->setPosition(Vec2(item2->getPosition()+Vec2(25,18)));
	item2->addChild(eradicantLabel);
	
	//种塔范围背景
	 auto towerBj =  Sprite::create("slice01.png");
	 towerBj->setName("towerBj");
	 towerBj->setPosition(Vec2(towers->getPosition()));
	 towerBj->setScale(towers->getScope()/(towerBj->getContentSize().width/2));
	 this->addChild(towerBj);

	Menu *menu = Menu::create(item1,item2,NULL);
	menu->alignItemsVerticallyWithPadding(70);
	menu->setPosition(towers->getPosition());
	this->addChild(menu);
	//升级所需要的钱
	upGradeMoney =  towers->getCurgold();
	updateLabel->setString(StringUtils::format("%d",upGradeMoney));
	//铲除你获得的钱
	 eradicantMoney =towers->getGoldvalue();
     eradicantLabel->setString(StringUtils::format("%d",eradicantMoney));
	 //如果等级大于三变成灰色
     if(towers->getCurlevel()>3)
	 {
       item1->setColor(Color3B::GRAY);
		 auto UpleveLabel= Label::createWithTTF("Max","Marker Felt.ttf",30);
	     UpleveLabel->setAnchorPoint(Vec2(0,0));
	     UpleveLabel->setPosition(Vec2(item2->getPosition()+Vec2(10,100)));
		 item1->addChild(UpleveLabel);
	     UpleveLabel->setColor(cocos2d::Color3B::WHITE);  
		 item1->removeChild(updateLabel);
	 }
	 
	 
}

void UpdateLayer::unshow()
{
	this->removeFromParentAndCleanup(true);  
}

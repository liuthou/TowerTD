#include "MonsterGuide.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
bool MonsterGuide::init(){
	if (!Layer::init())return false;
	layer = GUIReader::getInstance()->widgetFromJsonFile("GuideLayer_1/GuideLayer_1.json");
	this->addChild(layer);
	for (int i = 1;i<=4;i++){
		std::string name = StringUtils::format("Btn%d",i);
		auto btn = (Button*)(layer->getChildByName(name));
		btn->addTouchEventListener(CC_CALLBACK_2(MonsterGuide::guideTouch,this));
		buttons.pushBack(btn);
	}
	for (int i = 1; i<=4;i++){
		std::string name =StringUtils::format("btn_%d.png",i); 
		auto sp = Sprite::create(name); 
		sp->setPosition(480,480);
//		sp->setRotation(90);
		sp->setScaleX(0.87);
		sp->setScaleY(1.21);
		layer->addChild(sp);
		sp->setVisible(false);
		sp->setZOrder(100);
		guideSprite.pushBack(sp);
	}

	return true;
}
Scene* MonsterGuide::createScene(){
	auto scene =Scene::create();
	auto layer = MonsterGuide::create();
	scene->addChild(layer);
	return scene;
}
void MonsterGuide:: onEnter(){
	Layer::onEnter();
	 auto button = (Button*)(layer->getChildByName("Return"));
	 button->addTouchEventListener([=](Ref* sender,Widget::TouchEventType t){
		 if (t == Widget::TouchEventType::ENDED){
			 //////////////////////////////////音效////////////////////////////////////////////////////////
			 SimpleAudioEngine::getInstance()->playEffect("MonsterGuidButton.wav");
			 Director::getInstance()->popScene();
		 }
	 });


}
void MonsterGuide::guideTouch(Ref* sender,Widget::TouchEventType t){
	   auto name =((Button*)sender)->getName();
	  
	   if (name.compare("Btn1")==0 && t==Widget::TouchEventType::ENDED){
		   operateLayerVector(0);
		   //加音效/////////////////////////////////////////////////////////////////////////////
		   SimpleAudioEngine::getInstance()->playEffect("MonsterGuidButton.wav");
	   }else if(name.compare("Btn2")==0 && t==Widget::TouchEventType::ENDED){
		   operateLayerVector(1);
		   //加音效/////////////////////////////////////////////////////////////////////////////
		   SimpleAudioEngine::getInstance()->playEffect("MonsterGuidButton.wav");
	   }else if(name.compare("Btn3")==0 && t==Widget::TouchEventType::ENDED){
		   operateLayerVector(2);
		   //加音效/////////////////////////////////////////////////////////////////////////////
		   SimpleAudioEngine::getInstance()->playEffect("MonsterGuidButton.wav");
	   }else if(name.compare("Btn4")==0 && t==Widget::TouchEventType::ENDED){
		   operateLayerVector(3);
		   //加音效/////////////////////////////////////////////////////////////////////////////
		   SimpleAudioEngine::getInstance()->playEffect("MonsterGuidButton.wav");
	   }

}
void MonsterGuide::operateLayerVector(int index){
	log("heheheheheheheheheheehhehe");
      for (int i = 0;i<=3;i++){
		  if (i == index){
			auto sp = guideSprite.at(i);
			sp->setVisible(true);
			continue;
		  }

		auto sp = guideSprite.at(i);
		sp->setVisible(false);
	  }
}



#include "TowerSelect.h"
#include "GameBasic.h"
#include "GameManager.h"
#include "GameScene.h"
#include "StartScene.h"

bool TowerSelect::init(){
	if(!Layer::init()){
		return false;
	}
	GameManager::getInstance()->pause();
    count = 0;
	countLable = StringUtils::format("%d",count);
	auto uilayer = GUIReader::getInstance()->widgetFromJsonFile("startUI/Selet.json");
	this->addChild(uilayer);
	auto btn_ok = dynamic_cast<Button *>(uilayer->getChildByName("btn_ok"));
    auto propmt1 = dynamic_cast<ImageView *>(uilayer->getChildByName("prompt1"));
	auto propmt2 = dynamic_cast<ImageView *>(uilayer->getChildByName("prompt2"));
	btn_ok->addTouchEventListener([=](Ref *ref,Widget::TouchEventType t){
		if (t == Widget::TouchEventType::ENDED)
		{
			//GameManager::getInstance()->resume();
			if (count <= 0)
			{
				propmt1->setOpacity(255);
				propmt1->runAction(FadeOut::create(0.5));
				return;
			}
			auto call = CallFunc::create([&](){this->removeFromParentAndCleanup(true);
			     GameManager::getInstance()->resume();
			});
			auto scal = ScaleBy::create(0.2,0,0,0);
			this->runAction(Sequence::create(scal,call,nullptr));
		}
	});
	auto number = dynamic_cast<TextAtlas *>(uilayer->getChildByName("number_lable"));
	number->setString(countLable);
	auto scrollView = dynamic_cast<ScrollView *>(uilayer->getChildByName("ScrollView"));
	auto towerCheck = scrollView->getChildren();
	for (auto iter = towerCheck.begin();iter != towerCheck.end();iter++)
	{
	       auto check = dynamic_cast<CheckBox *>(*iter);
		   auto isEnable = UserDefault::getInstance()->getBoolForKey(check->getName().c_str(),false);
		   if (!isEnable)
		   {
			  check->setColor(Color3B::GRAY);
			  check->setEnabled(false);
			  continue;

		   }
		   check->addEventListener([=](Ref *ref,CheckBox::EventType t){
                 if (t == CheckBox::EventType::UNSELECTED)
			 {
				   count--;
				   countLable = StringUtils::format("%d",count);
				   number->setString(countLable);
				  auto &vc = GameManager::getInstance()->towerSelectVector;
                  for (auto it = vc.begin();it != vc.end();it++)
                  {
					  if ((*it) == check->getTag() - 1000)
					  {
						  vc.erase(it);
						  return;
					  }
                  }

			   }  
			   if (count >= 5)
			   {   
				   check->setSelectedState(false);
				   propmt2->setOpacity(255);
				   propmt2->runAction(FadeOut::create(0.5));
				   return;
			   }
			   if (t == CheckBox::EventType::SELECTED)
			   {
				   count++;
				   countLable = StringUtils::format("%d",count);
				   log("%d",count);
				   number->setString(countLable); 
				   GameManager::getInstance()->towerSelectVector.push_back(check->getTag() -1000);
			   }
			   
		   });

	}
	return true;
}
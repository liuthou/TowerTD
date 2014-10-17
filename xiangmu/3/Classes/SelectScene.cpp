#include "SelectScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace cocostudio;
using namespace ui;
bool SelectScene::init(){
	if (!Scene::init())return false;
	return true;
}
void SelectScene::onEnter(){
	Scene::onEnter();
	buttonIndex = 1;
	auto layer = GUIReader::getInstance()->widgetFromJsonFile("NewUi2_1/NewUi2_1.json");
	this->addChild(layer);
	 page1 = (PageView*)(layer->getChildByName("PageView_2"));
	auto panel1 = (Layout*)(page1->getChildByName("Panel_4"));
	 buttons = panel1->getChildren();
	for(auto  it = buttons.begin();it!=buttons.end();it++){
		auto button = (Button*)*it;
		button->setName(StringUtils::format("chapter%d.xml",buttonIndex));
		button->setTag(buttonIndex);
		button->addTouchEventListener(CC_CALLBACK_2(SelectScene::addTouchEventListener,this));
		buttonIndex++;
		log("%d",buttonIndex);
		auto sp = Sprite::create("SelectItem2.png");
		sp->setPosition(0,0);
		sp->setName("haha");
		sp->setAnchorPoint(Vec2(0,0));
		sp->setTag(buttonIndex*10);
		button->addChild(sp);
 }
	auto btn_left = (Button*)(layer->getChildByName("Left"));
	btn_left->addTouchEventListener(CC_CALLBACK_2(SelectScene::nextPage,this));
	auto btn_right = (Button*)(layer->getChildByName("Right"));
	btn_right->addTouchEventListener(CC_CALLBACK_2(SelectScene::nextPage,this));
	auto btn_return =(Button*)(layer->getChildByName("Return"));
	btn_return->addTouchEventListener(CC_CALLBACK_2(SelectScene::returnLastScene,this));
	this->readUserMessage();
}
void SelectScene::addTouchEventListener(Ref*sender,Widget::TouchEventType t){
	auto button = (Button*)(sender);
	std::string s = button->getName();
	int g = button->getTag();
	auto sp = (Sprite*)(button->getChildByName("haha"));
	log("myTag:::::::::::::::::%d",sp->getTag());
	if (sp->getTag()%10!=0 && t==Widget::TouchEventType::ENDED){
		///////////////音效//////////////////////////////////////////////////////
		SimpleAudioEngine::getInstance()->playEffect("MonsterGuidButton.wav");
		auto scene = MainScene::create(s.c_str(),g);
		Director::getInstance()->pushScene(scene);
	}
	log("__________________________________%s",s.c_str());

}
void SelectScene::nextPage(Ref* sender,Widget::TouchEventType t){
	///////////////音效//////////////////////////////////////////////////////

	auto btn = (Button*)sender;
	std::string name = btn->getName();
	if ( t == Widget::TouchEventType::ENDED&&name.compare("Left")==0){
		SimpleAudioEngine::getInstance()->playEffect("MonsterGuidButton.wav");
		pageIndex=page1->getCurPageIndex()-1;
		page1->scrollToPage(pageIndex);
	}else if ( t == Widget::TouchEventType::ENDED&&name.compare("Right")==0){
       	SimpleAudioEngine::getInstance()->playEffect("MonsterGuidButton.wav");
		pageIndex = page1->getCurPageIndex()+1;
		  page1->scrollToPage(pageIndex);
				 
	  }
	}
void SelectScene::returnLastScene(Ref* sender,Widget::TouchEventType t){

   Director::getInstance()->popScene();
}
//已受到全面保护
void SelectScene::setButtonTexture(int buttonIndex,std::string fileName,int tagnum){
	auto btn  =(Button*)(buttons.at(buttonIndex));
	auto sp = (Sprite*)btn->getChildByName("haha");
	sp->setTag(sp->getTag()+tagnum);
	sp->setTexture(fileName);
}
void SelectScene::readUserMessage(){
	//记录当前挑战的关卡,在GameScene中过关后应加"1"(第一次玩返回值为0)
	passedchapter = UserDefault::getInstance()->getIntegerForKey("passedchapter");
	std::string tmp_filecheckname;
	for (int i = 0;i<buttons.size();i++)
	{
		tmp_filecheckname = StringUtils::format("chapter%d.xml",i+1);
		//没有关卡文件
		if (!FileUtils::getInstance()->isFileExist(tmp_filecheckname))
		{
			setButtonTexture(i,"SelectItem2.png",0);
			continue;
		}
		//已过关
		if (i<passedchapter)
		{
			setButtonTexture(i,"SelectItem1.png",1);
		}
		//当前应该挑战关卡
		if (i==passedchapter)
		{
			setButtonTexture(i,"SelectItem0.png",1);
		}
		//无法挑战关卡
		if (i>passedchapter)
		{
			setButtonTexture(i,"SelectItem3.png",0);
		}
	}


}
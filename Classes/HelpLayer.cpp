#include "HelpLayer.h"
#include "StartScene.h"



LevelLayer::LevelLayer()
	
{}

LevelLayer::~LevelLayer()
{

}
Scene *LevelLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = LevelLayer::create();
	scene->addChild(layer);
	return  scene;
}

bool LevelLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

		int levelPages = 3; 
	     layerNum = 2;

	this->setIsVisble1(false);
	this->setIsVisble2(false);
	this->setIsVisble3(false);

    WINDOW_WIDTH =  Director::getInstance()->getVisibleSize().width;
	WINDOW_HEIGHT = Director::getInstance()->getVisibleSize().height;
	//背景
	auto bg = Sprite::create("loading0-hd.png");
	bg->setOpacity(50);
	bg->setScale(2);
	bg->setPosition(Vec2(WINDOW_WIDTH/2,WINDOW_HEIGHT/2));
	this->addChild(bg);

	Widget * uilayer = GUIReader::getInstance()->widgetFromJsonFile("MenuProject/NewUiMenu_1.json");
	uilayer->setPosition(Vec2(50,85));
	this->addChild(uilayer,1);
    auto image = uilayer->getChildByName("Image_1");
	//换页菜单
    auto menuitem3 = MenuItemImage::create("tr.png","we.png",CC_CALLBACK_0(LevelLayer::moveLeft,this));
    auto menuitem4 = MenuItemImage::create("re.png","qw.png",CC_CALLBACK_0(LevelLayer::moveRight,this));
    menu3 =Menu::create(menuitem3,NULL);
	menu3->setPosition(Vec2(WINDOW_WIDTH/2-490,WINDOW_HEIGHT/2-120));
	this->addChild(menu3);
	menu4 =Menu::create(menuitem4,NULL);
	menu4->setPosition(Vec2(WINDOW_WIDTH-150,WINDOW_HEIGHT/2-120));
	this->addChild(menu4);

	// 返回helpLayer
    auto backbutton = dynamic_cast<Button *>(uilayer->getChildByName("Button_14"));
	backbutton->addTouchEventListener([&](Ref *ref, Widget::TouchEventType t){
		
		Director::getInstance()->replaceScene(StartScene::createScene());
	});
	//介绍塔的菜单
	auto introbutton = dynamic_cast<Button *>(image->getChildByName("Button_18"));
	introbutton->addTouchEventListener([=](Ref *ref,Widget::TouchEventType t){
		if (t == Widget::TouchEventType::BEGAN)
		{
			introduceTower();			
		}
	});
	//关于界面
	auto aboutbutton = dynamic_cast<Button *>(image->getChildByName("Button_19"));
	aboutbutton->addTouchEventListener([=](Ref * ref , Widget::TouchEventType t){
		if(t == Widget::TouchEventType::BEGAN)
		{
	      	About();
		}
	});

   //帮助界面
	auto helpbutton = dynamic_cast<Button *>(image->getChildByName("Button_17"));
	helpbutton->addTouchEventListener([=](Ref * ref, Widget::TouchEventType t){
		if(t == Widget::TouchEventType::BEGAN)
		{
			help();
		}		
	});
     help();
     //触摸响应
	 auto touchListener = EventListenerTouchOneByOne::create();
	 touchListener->onTouchBegan = CC_CALLBACK_2(LevelLayer::onTouchBegan, this);
	 touchListener->onTouchMoved = CC_CALLBACK_2(LevelLayer::onTouchMoved, this);
	 touchListener->onTouchEnded = CC_CALLBACK_2(LevelLayer::onTouchEnded, this);
	 _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
     return true;
}


bool LevelLayer::onTouchBegan(Touch *touch, Event  *event)
{
	return true;
}

void LevelLayer::onTouchMoved(Touch *touch, Event  *event)
{
	layer->runAction(MoveBy::create(0.1f, Vec2(touch->getDelta().x, 0)));
}

void LevelLayer::onTouchEnded(Touch *touch, Event  *event)
{
	
	if (touch->getStartLocation().getDistance(touch->getLocation()) > WINDOW_WIDTH/ 3 )
	{
		
		
		if (layer->getPositionX() > layerPos.x  )
		{
			 if(layerPos.x > 0)
			 {
				layerPos.x = WINDOW_WIDTH/8-150;
			 }
			layerPos.x = (layerPos.x +WINDOW_WIDTH);	
			
		}

		else if (layer->getPositionX() < layerPos.x)
		{
			if(layerPos.x < 0)
			{
				layerPos.x = WINDOW_WIDTH/8-185;
			}
			layerPos.x = (layerPos.x -WINDOW_WIDTH);
		   
		}		 
	}
	layer->stopAllActions();
	layer->runAction(MoveTo::create((layer->getPosition().getDistance(layerPos)/WINDOW_WIDTH* 0.5f), layerPos));
}

void LevelLayer::help()
{	

	if(this->getIsVisble1())
	{
		return;
	}

	
	this->removeChildByName("layer3");
	this->removeChildByName("layer2");
	
	//这个是可以移动的层
	layer =Layer::create();
	layerPos = layer->getPosition();
	layer->setName("layer1");
    layer->setPosition(Vec2(0,0));
	this->addChild(layer,1);

	Widget* uiLayer =GUIReader::getInstance()->widgetFromJsonFile("NewUiProject_1/NewUiProject_1.json");
	uiLayer->setAnchorPoint(Vec2(0.5f,0.5f));
	uiLayer->setPosition(Vec2(WINDOW_WIDTH/2,WINDOW_HEIGHT/2));
	layer->addChild(uiLayer);
	Widget* uiLayer2 =GUIReader::getInstance()->widgetFromJsonFile("NewUiProject_1/NewUiProject_5.json");
	uiLayer2->setAnchorPoint(Vec2(0.5f,0.5f));
	uiLayer2->setPosition(Vec2(uiLayer->getPosition() + Vec2(WINDOW_WIDTH,0)));
	layer->addChild(uiLayer2);

	Widget* uiLayer3 =GUIReader::getInstance()->widgetFromJsonFile("NewUiProject_1/NewUiProject_3.json");
	uiLayer3->setAnchorPoint(Vec2(0.5f,0.5f));
	uiLayer3->setPosition(Vec2(-(WINDOW_WIDTH)+uiLayer->getPositionX(),WINDOW_HEIGHT/2));
	layer->addChild(uiLayer3);
	 this->setIsVisble1(true);
	 this->setIsVisble2(false);
	 this->setIsVisble3(false);

}
  
void LevelLayer::moveLeft()
{
	if(layer->getPosition().x<0)
	{
		return;
	}
	layer->runAction(MoveBy::create(1,Vec2(-WINDOW_WIDTH,0)));
	 
}

void LevelLayer::moveRight()
{
	if(layer->getPosition().x > 0)
	{
		return;				
	}
	layer->runAction(MoveBy::create(1,Vec2(WINDOW_WIDTH,0)));	
}

void LevelLayer::introduceTower()
{

	if(this->getIsVisble2())
	{
		return;
	}
	this->removeChildByName("layer3");
	this->removeChildByName("layer1");
	/*menu3->setVisible(true);
	menu4->setVisible(true);*/
	layer =Layer::create();
	layer->setPosition(Vec2(0,0));
	layer->setName("layer2");
	this->addChild(layer,2);

	Widget* bg3 =GUIReader::getInstance()->widgetFromJsonFile("NewUiProject_1/NewUiProject_4.json");
	bg3->setAnchorPoint(Vec2(0.5f,0.5f));
	bg3->setPosition(Vec2(WINDOW_WIDTH/2,WINDOW_HEIGHT/2));
	layer->addChild(bg3);

	Widget* bg1 =GUIReader::getInstance()->widgetFromJsonFile("NewUiProject_1/NewUiProject_6.json");
	bg1->setAnchorPoint(Vec2(0.5f,0.5f));
	bg1->setPosition(Vec2(-(WINDOW_WIDTH)+bg3->getPositionX(),WINDOW_HEIGHT/2));
    layer->addChild(bg1);

	Widget* bg2 =GUIReader::getInstance()->widgetFromJsonFile("NewUiProject_1/NewUiProject_7.json");
	bg2->setAnchorPoint(Vec2(0.5f,0.5f));
	bg2->setPosition(Vec2(bg3->getPosition().x+WINDOW_WIDTH,WINDOW_HEIGHT/2));
	layer->addChild(bg2);
	this->setIsVisble2(true);
	this->setIsVisble1(false);
	this->setIsVisble3(false);
}

void LevelLayer::About()
{
	this->stopAllActions();
	if(this->getIsVisble3())
	{
		return;
	}
	this->removeChildByName("layer1");
	this->removeChildByName("layer2");
	/* menu3->setVisible(false);
	menu4->setVisible(false);
	*/
	layer = Layer::create();
	layer->setPosition(Vec2(0,0));
	layer->setName("layer3");
	this->addChild(layer,3);

	Widget* uiLayer =GUIReader::getInstance()->widgetFromJsonFile("NewUiAbout_1/NewUiAbout_1.json");
    uiLayer->setAnchorPoint(Vec2(0.5f,0.5f));
	uiLayer->setPosition(Vec2(WINDOW_WIDTH/2,WINDOW_HEIGHT/2));
	layer->addChild(uiLayer);

	Widget* bg1 =GUIReader::getInstance()->widgetFromJsonFile("NewUiAbout_1/NewUiAbout_2.json");
	bg1->setAnchorPoint(Vec2(0.5f,0.5f));
	bg1->setPosition(Vec2(-(WINDOW_WIDTH)+uiLayer->getPositionX(),WINDOW_HEIGHT/2));
	layer->addChild(bg1);

	Widget* bg2 =GUIReader::getInstance()->widgetFromJsonFile("NewUiAbout_1/NewUiAbout_3.json");
	bg2->setAnchorPoint(Vec2(0.5f,0.5f));
	bg2->setPosition(Vec2(uiLayer->getPosition().x+WINDOW_WIDTH,WINDOW_HEIGHT/2));
	layer->addChild(bg2);

	

	this->setIsVisble3(true);
	this->setIsVisble1(false);
	this->setIsVisble2(false);
	
}
//
//  Room.cpp
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-13.
//
//

#include "Room.h"
#include "ProcessControl.h"
#include "Hall.h"
#include "AIPlayer.h"
#include "NormalPlayer.h"
#include "Config.h"
#include "Global.h"

using namespace TexasPoker;

//通过房间层创建场景
Scene * Room::createScene(int _id,int ScoreMax,int ScoreMin){
	auto scene = Scene::create();
	auto layer = Room::create(_id,ScoreMax,ScoreMin);
	scene->addChild(layer);
    
	return scene;
}

//创建房间
Room * Room::create(int _id,int ScoreMax,int ScoreMin){
	auto room = new Room();
	if (room && room->init(_id,ScoreMax,ScoreMin))
	{
		room->autorelease();
		return room;
	}
	CC_SAFE_DELETE(room);
	return NULL;
}

//房间层的初始化
bool Room::init(int _id,int ScoreMax,int ScoreMin){
	if (!Layer::init())
	{
		return false;
	}
    
	this->ID = _id;
    
	/**最多可携带最高金额*/
	this->ScoreMax = ScoreMax;
    
	/**最低下注金额*/
	this->ScoreMin = ScoreMin;
    
	//庄家的椅子初始化为1
	DealerPlayerChair = 1;
	
    initPlayerMenu();
    
	//向房间添加 AI玩家
	for (int i=1; i<10; i++) {
		std::string names = StringUtils::format("AIPlayer%d", i);
        
        srand((int)clock());
        auto s = rand() % 10 + 1;
        
        char sex = 'm';
        
        if(s > 5){
            sex = 'f';
        }
		
        auto  aiPlayer = AIPlayer::create(ePlayerGameState::NORMAL, i, names, sex, 50000, 50000);
        
        Site(aiPlayer);
	}
    
    
    /**初始化UI*/
    initUI();
    
	//向房间添加 Normal玩家
	/*auto normalPlayer = NormalPlayer::create(ePlayerGameState::NORMAL, 9, "normalPlayer", 'm', 5000, ScoreMin);
	Chairs_Players.insert(9, normalPlayer);*/
    
	return true;
}

void Room::initUI(){

    auto uiLayer = GUIReader::getInstance()->widgetFromJsonFile("UI/GameScene.ExportJson");
    uiLayer->setPosition(Vec2::ZERO);
    this->addChild(uiLayer,-1);
    
    auto img = uiLayer->getChildByName("Image_3");
    VoiceButton  = (Button *)img->getChildByName("Button_9");
    CCASSERT(VoiceButton != nullptr, "VoiceButton not nullptr");
    
    VoiceButton->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(
     CC_CALLBACK_2(Room::onTouchVoiceButton, this)
     ));
    
    initDila();
    
    auto language = Config::LANGUAGE::getInstance()->AT("Config").asValueMap();
	std::string cardTypeSort = language.at("CardTypeSort").asString();
	auto label = Label::createWithSystemFont(cardTypeSort,"Euphemia",18);
	label->setColor(cocos2d::Color3B(200,200,200));
	label->setPosition(567,280);
	this->addChild(label);
}

void Room::onEnter(){
    Layer::onEnter();
    
    /**
     *  播放背景音乐
     */
    intiAudio();
}

void Room::intiAudio(){
    log("Room::intiAudio");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("AUDIO/back.mp3",true);
}

void Room::onTouchVoiceButton(Ref*ref,ui::Widget::TouchEventType type){
    Hall::createRoom(Hall::HallType::CHINA);
}

void Room::initDila(){
    ArmatureDataManager::getInstance()->addArmatureFileInfo("ANIMATION/poke_girl.ExportJson");
    Dila = Armature::create("poke_girl");
    Dila->setPosition(560,530);
    this->addChild(Dila);
    Dila->getAnimation()->play("tip");
}

void Room::onEnterTransitionDidFinish(){
	Layer::onEnterTransitionDidFinish();
    
	//当玩家数量大于等于2时，开始进行控制流程操作
	if ( this->Chairs_Players.size() >= 2){
		ProcessControl *processControl = ProcessControl::create(this);
        this->addChild(processControl);
		processControl->Index();
        
		// 涉及到 贴层的问题: ProcessControl 和 PokerAction
	}else{
		log(" player not enught");
		DelayTime::create(10.0f);
        
	}
}

void Room::setDealerPlayerChair(){
	if(this->DealerPlayerChair ==9){
		this->DealerPlayerChair = 1;
	}else{
		this->DealerPlayerChair++;
	}
}

int Room::getDealerPlayerChair(){
	return this->DealerPlayerChair;
}

int Room::getID(){
	return ID;
}

int Room::getScoreMax(){
	return ScoreMax;
}

int Room::getScoreMin(){
	return ScoreMin;
}

Map<int, Player *> Room::getChairs_Players(){
	return Chairs_Players;
}

int Room::getPlayerCount(){
	PlayerCount = (int)Chairs_Players.size();
	return PlayerCount;
}

int Room::getPot(){
	return Pot;
}

bool Room::Site(Player * player){
    this->addChild(player);

    for(int i = 1; i<10; i++ ){
        if (Chairs_Players.at(i) == nullptr) {
            player->setPlayerIndex(i);
            Chairs_Players.insert(i, player);
            
            setPlayerMenu(player);
            
            PlayerCount++;
            return true;
            break;
        }
    }
    
    return false;
}

void Room::setPlayerMenu(Player* _player){
    int chair_number = _player->getPlayerIndex();
    
    MenuItemSprite * &playerItem = getPlayerItemByChairNumber(chair_number);
    
    auto normalSprite = Sprite::createWithSpriteFrameName("user_1.png");
    //auto normalSprite = Sprite::create("UI/GameScene_chair.png");
    playerItem = MenuItemSprite::create(normalSprite, normalSprite);
    
    setPlayerItemPositionByChairNumber(chair_number);
    
    Sprite * sexSprite;
    char sex  = _player->getSex();
    if( sex == 'm' ){
        sexSprite = Sprite::createWithSpriteFrameName("user_headboy.png");
    }else if(sex == 'f' ){
        sexSprite = Sprite::createWithSpriteFrameName("user_headgril.png");
    }
    sexSprite->setPosition(Vec2(55, 80));
    playerItem->addChild(sexSprite);
    
    float x = playerItem->getContentSize().width;
    float y = playerItem->getContentSize().height;
    
    auto label = Label::createWithSystemFont(_player->getName(), "Arial", 20);
    label->setName("topLabel");
    label->setPosition(x/2, y-20);
    playerItem->addChild(label);
    
    auto label2 = Label::createWithSystemFont(
                Function::getFormatScore(_player->getScore()), "Arial", 20);
    label2->setPosition(x/2, 15);
    label2->setName("bottomLabel");
    playerItem->addChild(label2);
    
    auto image = Sprite::create("UI/chippool_2.png");
    image->setName("chipPool");
    image->setVisible(false);
    playerItem->addChild(image);
    
    auto label3 = Label::createWithSystemFont("0", "Arial", 20);
    
    switch(chair_number){
        case 1: image->setPosition(20, -25); label3->setPosition(40, -25); 
            label3->setAnchorPoint(Vec2(0, 0.5)); break;
            
        case 2: image->setPosition(-20, 50); label3->setPosition(-40, 50); 
            label3->setAnchorPoint(Vec2(1, 0.5)); break;
            
        case 3: image->setPosition(-20, y); label3->setPosition(-40, y);
            label3->setAnchorPoint(Vec2(1, 0.5)); break;
            
        case 4: image->setPosition(20, y+20); label3->setPosition(40, y+20);
            label3->setAnchorPoint(Vec2(0, 0.5)); break;
            
        case 5: image->setPosition(20, y+20); label3->setPosition(40, y+20);
            label3->setAnchorPoint(Vec2(0, 0.5)); break;
            
        case 6: image->setPosition(x-20, y+20); label3->setPosition(x-40, y+20); 
            label3->setAnchorPoint(Vec2(1, 0.5)); break;
            
        case 7: image->setPosition(x+20, y-20); label3->setPosition(x+40, y-20); 
            label3->setAnchorPoint(Vec2(0, 0.5)); break;
            
        case 8: image->setPosition(x+20, 50);  label3->setPosition(x+40, 50); 
            label3->setAnchorPoint(Vec2(0, 0.5)); break;
            
        case 9: image->setPosition(x-20, -20); label3->setPosition(x-40, -20);  
            label3->setAnchorPoint(Vec2(1, 0.5)); break;
    }
    
    label3->setName("tempScoreLabel");
    label3->setVisible(false);
    
    playerItem->addChild(label3);

    playerMenu->addChild(playerItem);
}

MenuItemSprite * &Room::getPlayerItemByChairNumber(int chairNumber){
    switch(chairNumber){
        case 1 : return playerItem1; break;
        case 2 : return playerItem2; break;
        case 3 : return playerItem3; break;
        case 4 : return playerItem4; break;
        case 5 : return playerItem5; break;
        case 6 : return playerItem6; break;
        case 7 : return playerItem7; break;
        case 8 : return playerItem8; break;
        case 9 : return playerItem9; break;
    }
    return playerItem1;
}

void Room::setPlayerItemPositionByChairNumber(int chairNumber){
    switch(chairNumber){
        case 1 : playerItem1->setPosition(Vec2(785, 530)); break;
        case 2 : playerItem2->setPosition(Vec2(1010, 440)); break;
        case 3 : playerItem3->setPosition(Vec2(1010, 220)); break;
        case 4 : playerItem4->setPosition(Vec2(860, 150)); break;
        case 5 : playerItem5->setPosition(Vec2(568, 150)); break;
        case 6 : playerItem6->setPosition(Vec2(310, 150)); break;
        case 7 : playerItem7->setPosition(Vec2(90, 220)); break;
        case 8 : playerItem8->setPosition(Vec2(90, 440)); break;
        case 9 : playerItem9->setPosition(Vec2(340, 530)); break;
    }
}

void Room::initPlayerMenu(){
    playerMenu = Menu::create();
    playerMenu->setPosition(Vec2::ZERO);
    this->addChild(playerMenu);
}

void Room::startDilaTip(){
    Dila->getAnimation()->play("tip");
    //播放音效
}

void Room::stopDilaTip(){
    Dila->getAnimation()->stop();
    //停止音效
}

Player * Room::getPlayerByChairNumber(int chairNumber){
    return Chairs_Players.at(chairNumber);
}



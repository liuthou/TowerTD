
//
//  BackgroundLayer.cpp
//  heroJump
//
//  Created by mazhai on 14-9-17.
//
//

#include "BackgroundLayer.h"
#include "ConfigUtil.h"
#include "BigColoud.h"
#include "MidColoud.h"
#include "SmallColoud.h"
#include "ConfigUtil.h"
#include "JumpHelp.h"
#include "HitBodys.h"
#include "StoneLayer.h"
#include "GoldandGemLayer.h"
#include "GameOverScene.h"
#include "CCShake.h"
#include "BaseRewards.h"
#include "EnemyLayer.h"
#define N_TEST 0
void BackgroundLayer::onEnter(){
    Layer::onEnter();
    
   /* JumpParameter *jp = JumpParameter::create();
    jp->setMoveTime(12);
    jp -> setMove(true);
    jp->setUser_role_direction(DOWN);
   JumpHelp::getRoleSprite()->setJumpParameter(jp);*/
   
    
}

bool BackgroundLayer::init(){
    if (!Layer::init()) {
        return false;
    }
   
    
    this->setName("backgroundLayer");
    
    bigCloudProbablity = 10;//big coloud's probability
    quickMoveSpeed = 50;
    leftTime = 0;//remainder time
    allTime = 0;
    
    v0_Down = GRAVITY * allTime;//first speed of direction down.
    vt_Down = v0_Down;// direction down the speed of time t.
    moveDownSpeed = 500;
    v0_Up = 0;//direction up first speed.
    vt_Up = 0;//direction up the speed of time t.
    
    leftTime = 0;
    everyTimeLength = 0;//eveny frame the bg move length
    finalLength = 0;
    roleMoveDownLength = 0;
    
    curScoreLabel = Label::createWithSystemFont("000","Airal", 40);
    curScoreLabel->setPosition(70,880);
    curScoreLabel->setAnchorPoint(Vec2(0,0));
    curScoreLabel->setColor(cocos2d::Color3B::WHITE);
    this->addChild(curScoreLabel,10001);
    
    winsize = Director::getInstance()->getWinSize();
    auto bg1 = Sprite::create(BG1);
    bg1->setScale(winsize.height / bg1->getContentSize().height );
    bgsize  = bg1->getBoundingBox().size;
    
    center =  __NotificationCenter::getInstance();
    //center->addObserver(this, callfuncO_selector(BackgroundLayer::align), "BoudingWithTubberBand", nullptr);
    //add upLayer midLayer downLayer
    addUpLayer();
    addMidLayer();
    addDownLayer();

    //add  the Layer for change used
    currUpLayer = upLayer;
    currMidLayer = midLayer;
    currDownLayer = downLayer;
    
   
  // this->schedule(schedule_selector(BackgroundLayer::cloudsAppear), 10);
    
    //addToolLayer(midLayer);
    addToolLayer(upLayer);
//    jumpParameter = nullptr;
    /**
     *  删除移出屏幕的金币
     */
    this->schedule(schedule_selector(BackgroundLayer::deleteAllToolsFun));
    
    /**
     * 下移通知
     */
    center->addObserver(this, callfuncO_selector(BackgroundLayer::bgMoveDown), NOTIFICATIONCENTER_TO_SCREENS_DOWN, nullptr);
    
    /**
     *  颤抖效果通知
     */
    center->addObserver(this, callfuncO_selector(BackgroundLayer::backgroundShaky), NOTIFICATIONCENTER_TO_SHAKY,nullptr);
    /**
     *  接收到金币碰撞的通知。
     *
     */
    center->addObserver(this, callfuncO_selector(BackgroundLayer::addEatGoldScore), EAT_GOLD_REWARD_USER, nullptr);
    
    /**
     * 突发事件通知
     */
    //center->addObserver(this,  callfuncO_selector(BackgroundLayer::stopScheduleMethed), "Emergency", nullptr);
    /**
     * 重新运动通知
     */
    //center->addObserver(this,  callfuncO_selector(BackgroundLayer::startScheduleMethed), "RestartUpdate", nullptr);
    center->addObserver(this, callfuncO_selector(BackgroundLayer::gameOver), NOTIFICATIONCENTER_TO_GAME_OVER, nullptr);
    return true;
}

/**
 *  主角开始运动，
 */
void BackgroundLayer::bgMoveDown(Ref *sender){
    
    jumpParameter = ((JumpParameter*)sender);
    jumpParameter->retain();
    this->scheduleUpdate();
}


void BackgroundLayer::deleteAllToolsFun(float ft){
    addScore();
    
    /**
     *  回收屏幕下方石阶
     *
     */
    for (auto ite= HitBodys::getInstance()->getToolsBaseControlUserScript().begin(); ite != HitBodys::getInstance()->getToolsBaseControlUserScript().end();){
        if (!(*ite)) {
            ++ite;
            continue;
        }
        if (!((*ite) -> getParent())) {
            ++ite;
            continue;
        }
        
        if (!((*ite) -> getParent() -> getParent())) {
            ++ite;
            continue;
        }
        if((!((*ite) -> getDie())) && (*ite) -> getParent() -> getParent() -> getTag() == N_CURRDOWNLAYER){
            (*ite) -> setDie(true);
            break;
        }else{
            ++ite;
        }
   }
    for(auto ite= HitBodys::getInstance()->getToolsBaseControlUserScript().begin(); ite != HitBodys::getInstance()->getToolsBaseControlUserScript().end();)
	{
        if((*ite) -> getDie()){
            (*ite) -> die();
            break;
        }else{
            ++ite;
        }
    }
   
}


void BackgroundLayer::addUpLayer(){
    upLayer = Layer::create();
    auto bg1 = Sprite::create(BG1);
    bg1->setScale(winsize.height/bg1->getContentSize().height );
    bg1->setPosition(winsize/2);
    
    upLayer->addChild(bg1);
    upLayer->setName("upLayer");
    upLayer->setPosition(0, winsize.height + N_TEST);
    
    this->addChild(upLayer);
}


void BackgroundLayer::addMidLayer(){
    midLayer = Layer::create();
    auto bg2 = Sprite::create(BG2);
    bg2->setScale(winsize.height/bg2->getContentSize().height );
    bg2->setPosition(winsize/2);
    
    midLayer->addChild(bg2);
    midLayer->setName("midLayer");

    this->addChild(midLayer);
    


}


void BackgroundLayer::addDownLayer(){
    downLayer =Layer::create();
    auto bg3 = Sprite::create(BG3);
    bg3->setScale(winsize.height/bg3->getContentSize().height );
    bg3 -> setPosition(winsize/2);
    
    downLayer->setName("downLayer");
    downLayer->setPosition(0, -winsize.height - N_TEST);
    downLayer->addChild(bg3);
    
    this->addChild(downLayer);
}


void BackgroundLayer::update(float t){
//     upLayer->setPositionY(upLayer->getPositionY() - 300 * t);
//     downLayer->setPositionY(downLayer->getPositionY() - 300 * t);
//     midLayer->setPositionY(midLayer->getPositionY() - 300 * t);
   
    checkWeatherOverTheLimited();
    if (jumpParameter == nullptr) {
        return;
    }
    bool isMove = jumpParameter ->getMove();//wheather remove
    float allTime = jumpParameter->getMoveTime();//get move time
    auto direction = jumpParameter->getScreen_direction();//get bg move direction
    leftTime = allTime;
    v0_Down = GRAVITY * leftTime;
    if (isMove && leftTime >= 0 && v0_Down > 0) {
        leftTime -=t;
        jumpParameter -> setMoveTime(leftTime);
        //roleSprite-> setJumpParameter(jumpParameter);
        //bg move down
        if (direction == DOWN) {
            everyTimeLength = (v0_Down + v0_Down - GRAVITY * t) * t * 0.5;
            vt_Down -= GRAVITY * t;
            finalLength += everyTimeLength;
            upLayer->setPositionY(upLayer->getPositionY()-everyTimeLength);
            downLayer->setPositionY(downLayer->getPositionY()-everyTimeLength);
            midLayer->setPositionY(midLayer->getPositionY()-everyTimeLength);
            if(v0_Down < 400){//bg moveDown speed too smill
                leftTime = 0 ;
            }
            
            roleMoveDownLength = 0;
        }
        //bg move up
        else if(direction == UP){
            //everyTimeLength = v0_Up * t + 0.5 *(t * t * GRAVITY );
            everyTimeLength = t * moveDownSpeed;
            v0_Up += GRAVITY * t;
            roleMoveDownLength += everyTimeLength;
            
            upLayer->setPositionY(upLayer->getPositionY() + everyTimeLength);
            downLayer->setPositionY(downLayer->getPositionY() + everyTimeLength);
            midLayer->setPositionY(midLayer->getPositionY() + everyTimeLength);
            /**
             *  通知游戏结束
             */
            //post RoleDie notification
            JUMP_LOG("%f",finalLength);
            if (roleMoveDownLength > DIE_CONDITAINS) {
                gameOver(nullptr);
            }

        }
        
        //  if leftTime == 0 PostNotinfication
        
        /**
         *  主角上移结束
         */
        if (leftTime <= 0) {
            this->unscheduleUpdate();
            center->postNotification(NOTIFICATIONCENTER_TO_ROLE_OVER);
        }
    }
    
}

void BackgroundLayer::checkWeatherOverTheLimited(){
    float upLayerPY = upLayer->getPositionY();
    float downLayerPY = downLayer->getPositionY();
    float midLayerPY = midLayer->getPositionY();
    float downLimited = -bgsize.height * 1.98;
    float upLimited = -downLimited;
    /**
     *  direction toward down
     *  check the position wheather over the down limited
     */
    
    if (downLayerPY <= downLimited) {
        downLayer->setPositionY(upLayerPY + bgsize.height + N_TEST);
        currMidLayer = upLayer;
        currUpLayer = downLayer;
        currDownLayer = midLayer; //user for remove the tool
        
        currUpLayer ->setTag(N_CURRUPLAYER);
        currMidLayer ->setTag(N_CURRMIDLAYER);
        currDownLayer -> setTag(N_CURRDOWNLAYER);
        
        currUpLayer->setZOrder(N_CURRUPLAYERZORDER);
        currMidLayer->setZOrder(N_CURRMIDLAYERZORDER);
        currDownLayer->setZOrder(N_CURRDOWNLAYERZORDER);
        //just add tool to the upLayer
        addToolLayer(currUpLayer);
        

    }
    else if (midLayerPY <= downLimited) {
        midLayer->setPositionY(downLayerPY + bgsize.height + N_TEST);
        currMidLayer = downLayer;
        currUpLayer = midLayer;
        currDownLayer = upLayer;
        
        currUpLayer ->setTag(N_CURRUPLAYER);
        currMidLayer ->setTag(N_CURRMIDLAYER);
        currDownLayer -> setTag(N_CURRDOWNLAYER);
        
        
        currUpLayer->setZOrder(N_CURRUPLAYERZORDER);
        currMidLayer->setZOrder(N_CURRMIDLAYERZORDER);
        currDownLayer->setZOrder(N_CURRDOWNLAYERZORDER);        //just add tool to the upLayer
        addToolLayer(currUpLayer);

    }
    else if (upLayerPY <= downLimited) {
        upLayer->setPositionY(midLayerPY + bgsize.height + N_TEST);
        currMidLayer = midLayer;
        currUpLayer = upLayer;
        currDownLayer = downLayer;
        
        currUpLayer ->setTag(N_CURRUPLAYER);
        currMidLayer ->setTag(N_CURRMIDLAYER);
        currDownLayer -> setTag(N_CURRDOWNLAYER);
        
        currUpLayer->setZOrder(N_CURRUPLAYERZORDER);
        currMidLayer->setZOrder(N_CURRMIDLAYERZORDER);
        currDownLayer->setZOrder(N_CURRDOWNLAYERZORDER);
        //just add tool to the upLayer
        addToolLayer(currUpLayer);
    }
    
    /**
     *  direction toward up
     *  check the position wheather over the up limited
     */
    
    else if (upLayerPY > upLimited) {
        upLayer->setPositionY(downLayer->getPositionY() - bgsize.height - N_TEST);
        currMidLayer = downLayer;
        currUpLayer = midLayer;
        
        
        currUpLayer->setZOrder(N_CURRUPLAYERZORDER);
        currMidLayer->setZOrder(N_CURRMIDLAYERZORDER);
        currDownLayer->setZOrder(N_CURRDOWNLAYERZORDER);
//        log("%f",downLayer->getPositionY());
    }
    else if (midLayerPY > upLimited) {
        midLayer->setPositionY(upLayer->getPositionY() - bgsize.height - N_TEST);
        currMidLayer = upLayer;
        currUpLayer = downLayer;
        
        
        currUpLayer->setZOrder(N_CURRUPLAYERZORDER);
        currMidLayer->setZOrder(N_CURRMIDLAYERZORDER);
        currDownLayer->setZOrder(N_CURRDOWNLAYERZORDER);
    }
    else if (downLayerPY > upLimited) {
        downLayer->setPositionY(midLayer->getPositionY() - bgsize.height - N_TEST);
        currMidLayer = midLayer;
        currUpLayer = upLayer;
        
        
        currUpLayer->setZOrder(N_CURRUPLAYERZORDER);
        currMidLayer->setZOrder(N_CURRMIDLAYERZORDER);
        currDownLayer->setZOrder(N_CURRDOWNLAYERZORDER);
    }

}



void BackgroundLayer::cloudsAppear(float t){
    
    int r = CCRANDOM_0_1() * 100;
    if (r < bigCloudProbablity) {
        //apea bigcloud
        auto big = BigColoud::create(BIGCOLOUD_SPEED);
        currUpLayer->addChild(big);
    }else{
        r = CCRANDOM_0_1() * 100;
        //outpritf smallcloud
        int spe = r < quickMoveSpeed ? SMALLCOLOUD_SPEED : MIDCOLOUD_SPEED;
        //outpritf midcloud
        r = CCRANDOM_0_1() * 100;
        if (r < 20) {
            auto mid =  MidColoud::create(spe);
            currUpLayer->addChild(mid);
        }else{
            auto macsmall = SmallColoud::create(spe);
            currUpLayer->addChild(macsmall);
        }
    }
    
}
/**
 *  make the bgLayer align with the role
 */
void BackgroundLayer::align(Ref * sender){
    
    currUpLayer->setPositionY(currUpLayer->getPositionY() + 200);
    currMidLayer->setPositionY(currMidLayer->getPositionY() + 200);
    currDownLayer->setPositionY(currDownLayer->getPositionY() + 200);
}

//when the Emergency occure stop the schedule Update methed.
void BackgroundLayer::stopScheduleMethed(Ref * sender){
    this->unschedule(schedule_selector(BackgroundLayer::update));
}

//when the Emergency over restart the schedule Update methed.
void BackgroundLayer::startScheduleMethed(Ref * sender){
    this->scheduleUpdate();
}

void BackgroundLayer::addToolLayer(Layer *layer){
   auto stoneLayer = StoneLayer::create();
   layer->addChild(stoneLayer);
    
   auto goldadgemLayer = GoldandGemLayer::create();
   layer->addChild(goldadgemLayer);
    
    auto ememyLayer = EnemyLayer::create();
    currMidLayer->addChild(ememyLayer);
}

void BackgroundLayer::addScore(){
    auto scoreStr =StringUtils::format("%d",(int)finalLength/100);
    curScoreLabel->setString(scoreStr);
}


//bg shaky
void BackgroundLayer::backgroundShaky(Ref * sender){
     this -> runAction(CCShake::create(10.0f,2));
}


/**
 *  迟到金币之后分数是加上五分
 */
void BackgroundLayer::addEatGoldScore(Ref* sender){
    finalLength += N_EAT_GOLD_ADD_SCORE;
    BaseRewards *baseRewards = dynamic_cast<BaseRewards *>(sender);
    if (baseRewards) {
        baseRewards -> die();
    }
}

/**
 *  观察是否有结束游戏通知，或者主角的移动距离已经超出了下限
 *
 *  return null
 */
void BackgroundLayer::gameOver(Ref* sender){
     Director::getInstance()->replaceScene(GameOverScene::createScene(finalLength));
}
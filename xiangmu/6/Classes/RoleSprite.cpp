//
//  RoleSprite.cpp
//  heroJump
//
//  Created by mazhai on 14-9-19.
//
//

#include "RoleSprite.h"
#include "ToolsBaseControlUserScript.h"
#include "AudioUtil.h"
#include "RubberbandSprite.h"

#include "JumpHelp.h"
/**
 *  动作适配器
 */
void RoleSprite::actionAdapter(int actionId,float ft){
    int actionName = actions.at(actionId);
    JUMP_LOG("actionName=%d",actionName);
    switch (actionName) {

            /**
             *  准备起跳
             */

        case ROLE_PROPER_TO_JUMP:
            if(!prepareToJumpFlag){
                prepareToJump();
            }
            break;

            /**
             *  已经跳起在在本屏上升
             */

        case ROLE_JUMPING_FOR_MY_SCREEN:
            roleMoveUp(ft);
            break;

            /**
             *  已经跳起在在本屏上升已经到顶，判断是否发消息告诉背景下移
             */
        case ROLE_JUMPING_FOR_MY_SCREEN_END:
            judgeRoleIsUpMax();
            break;

            /**
             *  主角已经不动,后面屏幕在上升（实际是后面背景层下落）
             */
        case ROLE_JUMPING_FOR_BACKGROUND:
            backgroundDown(ft);
            break;
            
            /**
             *  主角已经收到背景层的消息，已经到顶
             */
        case ROLE_JUMPING_UP_END:
            backgroundDownMaxY();
            break;

            /**
             *  主角做下降准备
             */
        case ROLE_JUMPING_BORN:
            if (!bornFlag) {
                beBorn();
            }
            break;

            /**
             *  主角下降
             */
        case ROLE_JUMPING_BORNNING:
            roleMoveDown(ft);
            break;

        case ROLE_BE_BORN_FOR_FIERST:
            nowAction = ACTION_START_NUMBER;
            break;

        case ROLE_BE_BORN:
            screenToDown(ft);
            break;

        default:
            break;

    }
}
/**
 *  屏幕下移
 */
void RoleSprite::screenToDown(float ft){
    jParameter -> setUser_role_direction(Direction_ROLE::DOWN);
    jParameter -> setScreen_direction(Direction_ROLE::UP);
    jParameter -> setMove(true);
    jParameter -> setMoveTime(speedTime);
    center -> postNotification(NOTIFICATIONCENTER_TO_SCREENS_DOWN, jParameter);
}
/**
 *   初始化动作
 *   @param choose 选择第几套动作
 *   returns 对应的动作集合
 */
std::vector<int> RoleSprite::initActions(int choose){
    switch (choose) {
        case FIREST_ACTION:{
            nowActionType = FIREST_ACTION;
            return firestJumpActions;
        }
            break;
        case NOMAL_ACTION:{
            nowActionType = NOMAL_ACTION;
            return hitWoodActions;
        }
            break;
        default:
            return firestJumpActions;
            break;
    }
}
/**
 *  主角已经撞墙，做转身动作
 */
void RoleSprite::userHitWall(){
    AudioUtil::getInstance()->playEffect("knockWall.mp3");
    /**
     *  停止背景
     */
    jParameter -> setMove(false);
    jParameter -> setMoveTime(0);
    jParameter -> setUser_role_direction(Direction_ROLE::DOWN);
    /**
     *  停止schedule
     */
    this -> unschedule(schedule_selector(RoleSprite::startJump));
    /**
     *  做转身动作（以现在的相反方向为准）
     */
    if (user_jump_Direction == Direction_ROLE::LEFT) {
        user_jump_Direction = Direction_ROLE::RIGHT;
        this -> setRotation3D(Vec3(0, 0, 0));
    } else {
        user_jump_Direction = Direction_ROLE::LEFT;
        this -> setRotation3D(Vec3(0, 180, 0));
    }
    Vec2 vecTo = user_jump_Direction == Direction_ROLE::RIGHT ?Vec2(WHEN_USER_HIT_WALL_DIERCTION, 20) :Vec2(-WHEN_USER_HIT_WALL_DIERCTION, 20);
    auto moveTo = MoveBy::create(0.1, vecTo);
    Animate *animate = JumpHelp::getJumpAnimate(HITWALL_);
    auto sp = Spawn::create(moveTo,animate, NULL);
    auto dontMove = CallFunc::create([=]{
        this -> nowAction = 4;
        this -> degress = PI/2;
        this -> schedule(schedule_selector(RoleSprite::startJump));
    });
    auto seq = Sequence::create(sp,dontMove, NULL);
    this ->runAction(seq);
}

void RoleSprite::changeMinY(){
    minY = GET_WINDOWS_SIZE.height/4;
}

/**
 *  添加主角图片
 */
bool RoleSprite::addPic(){
    bool flag = true;
    tex = Director::getInstance() -> getTextureCache() -> addImage(ROLE_TEXTURE);
    t_width = tex -> getPixelsWide();
    t_height = tex -> getPixelsHigh();
    if (!Sprite::initWithTexture(tex, Rect(0, 0, t_width/4, t_height/4))) {
        flag = false;
    }
    for (int i = 0 ; i< 4; i++) {
        for (int j = 0 ; j < 4; j++) {
            Rect r(t_width*j/4,t_height*i/4,t_width/4,t_height/4);
            vrs.push_back(r);
        }
    }
    return flag;
}


/**
 *  初始化所有变量
 */
void RoleSprite::initAllParameter(){
    //firest set false
    jParameter = JumpParameter::create();
    jParameter -> retain();
    jParameter -> setMove(false);
	jParameter -> setUser_role_direction(Direction_ROLE::UP);
	jParameter -> setScreen_direction(Direction_ROLE::DOWN);
    //init
    maxX = GET_WINDOWS_SIZE.width - (this -> getContentSize().width/2);
    maxY = GET_WINDOWS_SIZE.height / 2;
    minX = (this -> getContentSize().width)/2;
    minY = this -> getContentSize().height/2;
    ActionHelper::initJumpActions();
    /**
     *  第一次起跳的动作组，和用户碰到辅助道具的动作组
     */
    firestJumpActions = ActionHelper::getFirest_jump();
    hitWoodActions = ActionHelper::getHit_wood_jump();
    roleHp = 100;
    actions = initActions(FIREST_ACTION);
    bornFlag = false;
	nowAction = 0;
    degress = PI/2;
}


/**
 *  调整主角脸的朝向
 */
void RoleSprite::makeRoleFaceOrientation(){
    if (user_jump_Direction == Direction_ROLE::LEFT) {
        this -> setRotation3D(Vec3(0, 180, 0));
    } else {
        this -> setRotation3D(Vec3(0, 0, 0));
    }
}

void RoleSprite::roleMoveUp(float ft){
    if (this -> getPositionX() > maxX || this -> getPositionX() < minX) {
        userHitWall();
    }
    float speedX = user_jump_Direction == Direction_ROLE::LEFT ? -ft*cos(degress)*USER_SPEED:ft*cos(degress)*USER_SPEED;
    this -> setPosition(Vec2(this -> getPositionX() + speedX, this -> getPositionY() + sin(degress)*USER_SPEED*ft));
    if (this -> getPositionY() >= maxY) {
        nowAction++;
    }
}


void RoleSprite::roleMoveDown(float ft){
    this -> setPosition(Vec2(this -> getPositionX(), this -> getPositionY() - ft * USER_SPEED));
    if (this -> getPositionY() <= minY) {
        nowAction++;
    }
}


/**
 *  背景向下
 */
void RoleSprite::backgroundDown(float ft){
    if (degress!= PI/2) {
        if (this -> getPositionX() > maxX || this -> getPositionX() < minX) {
            userHitWall();
        }
        float speedX = user_jump_Direction == Direction_ROLE::LEFT ? -ft*cos(degress)*USER_SPEED:ft*cos(degress)*USER_SPEED;
        this -> setPositionX(this -> getPositionX() + speedX);
    }
}

void RoleSprite::backgroundDownMaxY(){
    nowAction++;
}


/**
 *  判断用户状态
 *  已经到达最上面了,判断是否给背景发消息
 */
void RoleSprite::judgeRoleIsUpMax(){
    jParameter -> setUser_role_direction(Direction_ROLE::UP);
    jParameter -> setScreen_direction(Direction_ROLE::DOWN);
    jParameter -> setMove(true);
    jParameter -> setMoveTime(speedTime);
    center -> postNotification(NOTIFICATIONCENTER_TO_SCREENS_DOWN, jParameter);
    nowAction++;
}

/**
 *  判断用户状态
 *  已经到达最下面了,判断是否给背景发消息
 */
void RoleSprite::judgeRoleIsDownMax(){
    nowAction++;
}

/**
 *  主角在屏幕中移动，此方法写在帧动画中~
 */
void RoleSprite::moveInThisScreen(float ft){
}


bool RoleSprite::init(){
    if (!addPic()) {
        return false;
    }
    broadCastRegist();
    initAllParameter();
    
    compatibleFun();

    

    this -> useToolsBaseSprite = nullptr;
    this -> schedule(schedule_selector(RoleSprite::startJump));

    roleDizzy();
    return true;
}

RoleSprite::~RoleSprite(){
    center = __NotificationCenter::getInstance();
    center -> removeObserver(this, NOTIFICATIONCENTER_ROLE_JUMP_TYPE);
    /**
     * 碰到操作型道具
     */
    center -> removeObserver(this, NOTIFICATIONCENTER_ROLE_JUMP_FOR_TOOLS_TYPE);
    /**
     * 屏幕通知主角下移
     */
    center -> removeObserver(this, NOTIFICATIONCENTER_TO_SCREENS_DOWN);
    jParameter -> release();
}


void RoleSprite::prepareToJump(){
    AudioUtil::getInstance()->playEffect("hai.wav");
    this -> stopAllActions();
    this -> unschedule(schedule_selector(RoleSprite::startJump));
    jParameter -> setUser_role_direction(Direction_ROLE::UP);
    jParameter -> setScreen_direction(Direction_ROLE::DOWN);
    jParameter -> setMove(false);
    jParameter -> setMoveTime(0);
    center -> postNotification(NOTIFICATIONCENTER_TO_SCREENS_DOWN, jParameter);
    
    
    jumppingFlag = false;
    makeRoleFaceOrientation();

    Animate *animate = JumpHelp::getJumpAnimate(PREPARETOJUMP_);
    auto dontMove = CallFunc::create([=]{
        this -> moveFlag = true;
        this -> prepareToJumpFlag = false;
        collitionHight = makeJumpHight();
        if (this -> useToolsBaseSprite !=nullptr && !(this -> useToolsBaseSprite ->isDie)) {
            this -> useToolsBaseSprite -> die();
            this -> useToolsBaseSprite = NULL;
        }
        this -> jParameter -> setUser_role_direction(Direction_ROLE::UP);
        this -> nowAction++;
        this -> schedule(schedule_selector(RoleSprite::startJump));
    });
    RubberbandSprite *rbs = NULL;
    if (useToolsBaseSprite!= NULL && !(useToolsBaseSprite -> isDie)) {
        rbs = dynamic_cast<RubberbandSprite*>(useToolsBaseSprite);
    }
    
    Action* sequence;
    if (rbs != NULL) {
        
        auto waitFor = CallFunc::create([=]{
            this -> moveFlag = true;
            this -> prepareToJumpFlag = false;
            this -> collitionHight = makeJumpHight();
            this -> jParameter -> setUser_role_direction(Direction_ROLE::UP);
            this -> nowAction++;
            this -> schedule(schedule_selector(RoleSprite::startJump));
            rbs -> startShake();
        });
        auto waitAction = CallFunc::create([=]{
            if (useToolsBaseSprite==NULL || useToolsBaseSprite == nullptr || useToolsBaseSprite -> isDie) {
                return;
            }
            RubberbandSprite *rbs = dynamic_cast<RubberbandSprite*>(useToolsBaseSprite);
            if (rbs && rbs !=nullptr && !(rbs ->isDie)) {
                rbs -> die();
                this -> useToolsBaseSprite = NULL;
            }
        });
        sequence = Sequence::create(animate,waitFor,RotateBy::create(0.5,0),waitAction, NULL);
    } else {
        sequence = Sequence::create(animate,dontMove, NULL);
    }

    
    this -> runAction(sequence);
}
void RoleSprite::sendDieCast(){
    center -> postNotification(NOTIFICATIONCENTER_TO_GAME_OVER);
}

void RoleSprite::jumping(){
    this -> stopAllActions();
    jumppingFlag = true;
    makeRoleFaceOrientation();
    auto animate = JumpHelp::getJumpAnimate(JUMPING_);
    this -> runAction(animate);
}


void RoleSprite::beBorn(){
    this -> stopAllActions();
    bornFlag = true;
    makeRoleFaceOrientation();
    auto animate = JumpHelp::getJumpAnimate(BEBORN_);
    auto dontMove = CallFunc::create([=]{
        moveFlag = false;
        bornFlag = false;
        nowAction++;
        jParameter -> setUser_role_direction(Direction_ROLE::DOWN);
    });
    auto spawn = Spawn::create(animate,dontMove, NULL);
    this -> runAction(spawn);
}

/**
 *  如果moveFlag(总开关打开)则进入帧动画
 *
 *  @param ft ft description
 */
void RoleSprite::startJump(float ft){
    actionAdapter(nowAction,ft);
}


void RoleSprite::firestJump(){
    moveFlag = false;
    upFlag = true;
    jumppingFlag = false;
    prepareToJump();
}

/**
 *  收听广播
 */
void RoleSprite::broadCastRegist(){

    center = __NotificationCenter::getInstance();
    /**
     *  碰到系统安排的道具
     */
    center -> addObserver(this, callfuncO_selector(RoleSprite::roleCollition), NOTIFICATIONCENTER_ROLE_JUMP_TYPE, nullptr);
    /**
     * 碰到操作型道具
     */
    center -> addObserver(this, callfuncO_selector(RoleSprite::roleCollitionForTools), NOTIFICATIONCENTER_ROLE_JUMP_FOR_TOOLS_TYPE, nullptr);

    center -> addObserver(this, callfuncO_selector(RoleSprite::backgourndIsStop), NOTIFICATIONCENTER_TO_ROLE_OVER, nullptr);

}

void RoleSprite::backgourndIsStop(Ref* sender){
    nowAction++;
}

void RoleSprite::screenToMeDown(Ref *sender){

}

void RoleSprite::roleCollition(Ref *sender){
    AudioUtil::getInstance()->playEffect("upthrust5.mp3");
    
    upFlag = true;
    moveFlag = false;
    UseToolsBaseSprite *utb = dynamic_cast<UseToolsBaseSprite*>(sender);
    CCASSERT(utb, "this UseToolsBaseSprite can't cast!!");

    this -> useToolsBaseSprite = utb;
    speedTime = utb -> getRoleSpeedTime();
    int redians = utb -> getRedians();
    if (redians == 90) {
        user_jump_Direction = Direction_ROLE::UP;
        this -> degress = PI/2;
    } else {
        if (redians > 90) {
            user_jump_Direction = Direction_ROLE::RIGHT;
        } else {
            user_jump_Direction = Direction_ROLE::LEFT;
        }
        this -> degress = CC_DEGREES_TO_RADIANS(abs(90 - redians));
    }
    actions = initActions(NOMAL_ACTION);
    nowAction = ACTION_START_NUMBER;
    changeMinY();
}


void RoleSprite::roleCollitionForTools(Ref *sender){
    ToolsBaseControlUserScript *utb = dynamic_cast<ToolsBaseControlUserScript*>(sender);
    if (utb -> controleRoleSpeed() != NO_CHANGE_ROLE_SPEED) {
        upFlag = true;
        moveFlag = false;
        jParameter -> setMove(false);
    
        CCASSERT(utb, "this ToolsBaseControlUserScript can't cast!!");
        user_jump_Direction = Direction_ROLE::UP;
        this -> degress = PI/2;
    
        speedTime = utb -> controleRoleSpeed();
        actions = initActions(NOMAL_ACTION);
        nowAction = ACTION_START_NUMBER;
        changeMinY();
    }
}



void RoleSprite::cleanObj(float t,UseToolsBaseSprite* obj){
    if (nullptr != obj && !(obj ->isDie)) {
         obj -> die();
    }
}


float RoleSprite::makeJumpHight(){
    float nowY = this ->getPositionY() - this -> getContentSize().height/2;
    return (nowY/maxY) * speedTime < 0.1?0:( nowY/maxY) * speedTime;
}


void RoleSprite::onEnter(){
    Sprite::onEnter();
    firestJump();
}

void RoleSprite::hitIce(){
    /**
     *  停止背景
     */
    jParameter -> setMove(false);
    jParameter -> setMoveTime(0);
    jParameter -> setUser_role_direction(Direction_ROLE::DOWN);
    Animate *animate = JumpHelp::getJumpAnimate(PREPARETOJUMP_);
    /**
     *  停止schedule
     */
    this -> unschedule(schedule_selector(RoleSprite::startJump));
    auto dontMove = CallFunc::create([=]{
        this -> nowAction = 4;
        this -> schedule(schedule_selector(RoleSprite::startJump));
    });
    this -> runAction(Sequence::create(animate,dontMove, NULL));
}
void RoleSprite::hitDoubi(){
    /**
     *  停止背景
     */
    jParameter -> setMove(false);
    jParameter -> setMoveTime(0);
    jParameter -> setUser_role_direction(Direction_ROLE::DOWN);
    Animate *animate = JumpHelp::getJumpAnimate(PREPARETOJUMP_);
    auto rotation = MoveBy::create(0.1, Vec2(0, -20));
    /**
     *  停止schedule
     */
    this -> unschedule(schedule_selector(RoleSprite::startJump));
    auto dontMove = CallFunc::create([=]{
        this -> nowAction = 4;
        this -> schedule(schedule_selector(RoleSprite::startJump));
    });
    this -> runAction(Sequence::create(animate,rotation,dontMove, NULL));
}
void RoleSprite::acttck(int aHp){
    this -> roleHp -= aHp;
    if(roleHp >= ROLE_HP_INIT){
        roleHp = ROLE_HP_INIT;
    }
    
    if(roleHp <= ROLE_HP_INIT /4){
        //发送警告
        warning();
    } else {
        //发送正常
        closeWarning();
    }
    
    if(roleHp <= 0){
        sendDieCast();
    } else {
        JumpHelp::getChooseToolsLayer() -> getSkillButton() -> startCd(roleHp);
    }
}
/**
 *  警告
 */
void RoleSprite::warning(){
    center -> postNotification(NOTIFICATIONCENTER_TO_OPEN_ALARM);
}
/**
 *  关闭警告
 *
 */
void RoleSprite::closeWarning(){
    center -> postNotification(NOTIFICATIONCENTER_TO_COLOSE_ALARM);
}
/**
 *  //FIXME 做兼容的方法，版本稳定后删除次方法
 */
void RoleSprite::compatibleFun(){

}

void RoleSprite::roleDizzy(){
    //auto dizzy = RoleDizzy::create();
    //this->addChild(dizzy);
    
}

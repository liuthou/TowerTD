//
//  RoleSprite.h
//  heroJump
//  本类使用开关来控制每个动画结束后的动作，然后使用vector来封装每个动作
//  Created by mazhai on 14-9-19.
//
//

#ifndef __heroJump__RoleSprite__
#define __heroJump__RoleSprite__

#include <iostream>
#include "cocos2d.h"
#include "ConfigUtil.h"
#include "JumpParameter.h"
#include "UseToolsBaseSprite.h"
#include "ActionHelper.h"

USING_NS_CC;
#define USER_SPEED 450
/**
 *  主角初始血量
 */
#define ROLE_HP_INIT 100
/**
 *  用户动作组从什么位置开始
 */
#define ACTION_START_NUMBER 0
#define WHEN_USER_HIT_WALL_DIERCTION 40
class RoleSprite :public Sprite{
private:
    float degress;
    int roleHp;
    Texture2D *tex;
    float t_width;
    float t_height;
    //max role jump distance
    float maxY;
    float maxX;
    float minX;
    float minY;
    std::vector<int> firestJumpActions;
    std::vector<int> hitWoodActions;
    __NotificationCenter* center;
    /**
     *  主角本次起跳，跳起的时间和高度
     */
    float collitionHight;
    float nowSenderTime;
    /**
     *  动作图片的坐标集合
     */
    std::vector<Rect> vrs;
    /**
     *  判断用户现在是否可以运动
     */
    bool moveFlag;
    /**
     *  是否是向上
     */
    bool upFlag;
    /**
     *  是否是跳跃中
     */
    bool jumppingFlag;
    /**
     *  是否在做下降准备
     */
    bool bornFlag;
    /**
     *  是否使用过道具，如果没有的话则做默认跳跃
     *  此变量主要负责让系统第一次调用的时候，主角默认在屏幕中跳跃
     */
    bool isNoCollitionFlag;
    
    /**
     *  因为每个物体的“弹力”都不相同，此变量保存物体使主角弹起的时间
     */
    int speedTime;
    /**
     *  当前的动作在序列中得位置
     */
    int nowAction;
    /**
     *  动作组合
     */
    std::vector<int> actions;
    /**
     *  当前的动作组类型
     */
    int nowActionType;
    /**
     *  当前用户跳得方向
     */
    Direction_ROLE user_jump_Direction;
    /**
     *  初始化所有变量
     */
    void initAllParameter();
    /**
     *  添加主角图片
     */
    bool addPic();
    /**
     *  注册消息中心
     */
    void broadCastRegist();
    /**
     *  调整主角脸的朝向
     */
    void makeRoleFaceOrientation();
    /**
     *  根据当前用户的起跳来判断，主角让屏幕移动的距离
     *
     *  @return 距离
     */
    float makeJumpHight();
    /**
     *  主角和普通物体碰撞
     *
     *  @param sender 碰撞的物体
     */
    void roleCollition(Ref *sender);
    /**
     *  主角和可操作物体碰撞
     *
     *  @param sender 碰撞的物体
     */
    void roleCollitionForTools(Ref *sender);
    /**
     *  屏幕通知主角下移
     *
     *  @param sender 碰撞的物体
     */
    void screenToMeDown(Ref *sender);
    /**
     *  主角在屏幕中移动，此方法写在帧动画中~
     */
    void moveInThisScreen(float ft);
    /**
     *  判断用户状态
     *  已经到达最上面了,判断是否给背景发消息
     */
    void judgeRoleIsUpMax();
    /**
     *  判断用户状态
     *  已经到达最下面了,判断是否给背景发消息
     */
    void judgeRoleIsDownMax();
    /**
     *  主角在本屏向上跳跃
     */
    void roleMoveUp(float ft);
    /**
     *  主角在本屏向下
     *
     */
    void roleMoveDown(float ft);
    
    /**
     *  //FIXME 做兼容的方法，版本稳定后删除次方法
     */
    void compatibleFun();
    /**
     *   初始化动作
     *   @param choose 选择第几套动作
     :returns: 对应的动作集合
     */
    std::vector<int> initActions(int choose);
    
    /**
     *  屏幕正在下降
     */
    void backgroundDown(float ft);
    void backgroundDownMaxY();
    /**
     *  主角已经撞墙做转身动作
     */
    void userHitWall();
    /**
     *  后面背景已经停止
     */
    void backgourndIsStop(Ref* sender);
    void changeMinY();
    void screenToDown(float ft);
public:
    virtual bool init();
    CREATE_FUNC(RoleSprite);
    /**
     *  准备起跳
     */
    virtual void prepareToJump();
    /**
     *  跳跃中
     */
    virtual void jumping();
    /**
     *  跳跃结束落地
     */
    virtual void beBorn();
    virtual void onEnter();
    void hitDoubi();
    virtual void cleanObj(float t,UseToolsBaseSprite* obj);
    /**
     *  user firest jump
     */
    virtual void firestJump();

    /**
     *  主角碰撞的物体
     */
    UseToolsBaseSprite* useToolsBaseSprite;
    virtual ~RoleSprite();

    /**
     *  是否是正在准备起跳
     */
    bool prepareToJumpFlag;
    virtual void startJump(float ft);
    /**
     *  主角碰到冰
     */
    void hitIce();
    /**
     *  动作适配器
     */
    virtual void actionAdapter(int actionId,float ft);
    
    /**
     *  封装用户动作的实体类
     */
    JumpParameter* jParameter;
    /**
     *  主角中招
     */
    void acttck(int aHp);
    void warning();
    void closeWarning();
    int getRoleHp(){
        return this -> roleHp;
    }
    void sendDieCast();
	void roleDizzy();
};


#endif /* defined(__heroJump__RoleSprite__) */

//
//  ActionHelp.h
//  heroJump
//
//  Created by mazhai on 14-9-29.
//
//

#ifndef __heroJump__ActionHelp__
#define __heroJump__ActionHelp__

#include <iostream>
#include <vector>

using namespace std;

typedef enum{
    /**
     *  准备起跳
     */
    ROLE_PROPER_TO_JUMP = 0x023,
    /**
     *  已经跳起在在本屏上升
     */
    ROLE_JUMPING_FOR_MY_SCREEN,
    /**
     *  已经跳起在在本屏上升已经到顶，判断是否发消息告诉背景下移
     */
    ROLE_JUMPING_FOR_MY_SCREEN_END,
    /**
     *  主角已经不动,后面屏幕在上升（实际是后面背景层下落）
     */
    ROLE_JUMPING_FOR_BACKGROUND,
    /**
     *  主角已经收到背景层的消息，已经到顶
     */
    ROLE_JUMPING_UP_END,
    /**
     *  主角做下降准备
     */
    ROLE_JUMPING_BORN,
    /**
     *  主角下降
     */
    ROLE_JUMPING_BORNNING,
    /**
     *  已经落地(第一次加载时候的降落到底，主角应该往上跳)
     */
    ROLE_BE_BORN_FOR_FIERST,
    /**
     *  用户已经降落到底，应该通知背景向上（这样）
     */
    ROLE_BE_BORN,
    /**
     *  用户撞到物体
     */
    ROLE_SHOT_BODY
} ROLE_NEXT_STATE;


typedef enum{
    FIREST_ACTION = 0x089,
    NOMAL_ACTION
} ACTION_NUMBER;

typedef enum{
    USE_WOOD=0,
    USE_RUBBERBAND
}NOW_USE_TYPE;


class ActionHelper{
private:
    static vector<int> firest_jump;
    static vector<int> hit_wood_jump;
public:
    static vector<int> getFirest_jump();
    
    static vector<int> getHit_wood_jump();
    
    
    static void initJumpActions();
};

#endif /* defined(__heroJump__ActionHelp__) */

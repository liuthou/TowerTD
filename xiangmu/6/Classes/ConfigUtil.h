//
//  ConfigUtil.h
//  heroJump
//
//  Created by mazhai on 14-9-17.
//
//

/**
  *add by mabs 用来存放一些宏和常量
  */
#ifndef __heroJump__ConfigUtil__
#define __heroJump__ConfigUtil__

#include <iostream>
#include "SystemMarcoUtil.h"
#define GRAVITY 50.8
#define N_CURRMIDLAYERZORDER 2
#define N_CURRUPLAYERZORDER 1
#define N_CURRDOWNLAYERZORDER 3

#define DIELENGTH GET_WINDOWS_SIZE.height *0.5
#define N_EAT_GOLD_ADD_SCORE 500
//==================================================open and colose alarm========================================================================

#define NOTIFICATIONCENTER_TO_OPEN_ALARM "NOTIFICATIONCENTER_TO_OPEN_ALARM"
#define NOTIFICATIONCENTER_TO_COLOSE_ALARM "NOTIFICATIONCENTER_TO_COLOSE_ALARM"
//=================================================image begin==========================================================================

#define ROLE_JUMP_PLIST "jump/roleJump.plist"
#define ROLE_PNG "role_1.png"
#define ROLE_HEADER_PNG "role/MainRole.png"
#define FILENAME1 "GoldandGem/1.png"
#define FILENAME2 "GoldandGem/2.png"
#define FILENAME3 "GoldandGem/3.png"
#define FILENAME4 "GoldandGem/4.png"
#define FILENAME5 "GoldandGem/5.png"
#define FILENAME6 "GoldandGem/6.png"
#define FILENAME7 "GoldandGem/7.png"
#define FILENAME8 "GoldandGem/8.png"

#define ONEHUNDRED 100
#define TEN 10
#define FIVE 5
#define NITHFIVE 95
#define HALF 50
#define TOOLS_WOOD_PNG "tools/mood3.png"
#define ROLE_TEXTURE "role/MainRole.png"
//=================================================image end==========================================================================

//=================================================differentLayer start===========================================================
#define N_CURRUPLAYER   8998
#define N_CURRMIDLAYER 8999
#define N_CURRDOWNLAYER 9000
//=================================================differentLayer end==============================================================





//=================================================cocos UI'S Name begin============================================================
#define LAYER_NAME_ROLELAYER "LAYER_NAME_ROLELAYER"
#define LAYER_NAME_SCORELAYER "LAYER_NAME_SCORELAYER"
#define LAYER_NAME_TOOLSLAYER "LAYER_NAME_TOOLSLAYER"
#define LAYER_NAME_BACKGROUNDLAYER "LAYER_NAME_BACKGROUNDLAYER"
#define LAYER_NAME_BROADCASTLAYER "LAYER_NAME_BROADCASTLAYER"
#define LAYER_NAME_INJUREDEFFECT "LAYER_NAME_INJUREDEFFECT"
#define LAYER_NAME_CHANGE_TOOLS "LAYER_NAME_CHANGE_TOOLS"
#define ROLE_SPRITE "ROLE_SPRITE"
#define LAYER_NAME_ROLE_ANIMATION_LAYER "LAYER_NAME_ROLE_ANIMATION_LAYER"

//=================================================cocos UI'S Name end============================================================
//=================================================enum begin============================================================
typedef enum {
    DOWN = 0,
    LEFT,
    RIGHT,
    UP
}Direction_ROLE;
//=================================================enum end============================================================

//=================================================jump begin============================================================
#define ROLE_ANIMATION_PNG_SPEED 0.4f
#define PREPARETOJUMP_ tex,vrs, 6, 2
#define JUMPING_ tex,vrs, 7, 2
#define BEBORN_ tex,vrs, 7, 4
#define HITWALL_ tex,vrs, 0, 4,0.1f
//=================================================jump end============================================================

//=================================================NotificationCenter begin=========================================
/**
 *  碰到系统安排的道具
 */
#define NOTIFICATIONCENTER_ROLE_JUMP_TYPE "NOTIFICATIONCENTER_ROLE_JUMP_TYPE"
/**
 * 碰到操作型道具
 */
#define NOTIFICATIONCENTER_ROLE_JUMP_FOR_TOOLS_TYPE "NOTIFICATIONCENTER_ROLE_JUMP_FOR_TOOLS_TYPE"
/**
 *  主角通知屏幕上移
 */
#define NOTIFICATIONCENTER_TO_SCREENS_UP "NOTIFICATIONCENTER_TO_SCREENS_UP"
/**
 *  屏幕通知主角下移已经结束
 */
#define NOTIFICATIONCENTER_TO_ROLE_OVER "NOTIFICATIONCENTER_TO_ROLE_OVER"
/**
 *  主角通知屏幕下移
 */

#define NOTIFICATIONCENTER_TO_SCREENS_DOWN "NOTIFICATIONCENTER_TO_SCREENS_DOWN"
/**
 *  主角通知屏幕运动结束
 */
#define NOTIFICATIONCENTER_TO_SCREENS_STOP "NOTIFICATIONCENTER_TO_SCREENS_STOP"
/**
 *  屏幕通知游戏结束
 */
#define NOTIFICATIONCENTER_TO_GAME_OVER "NOTIFICATIONCENTER_TO_GAME_OVER"

/**
 * 屏幕颤抖
 */
#define NOTIFICATIONCENTER_TO_SHAKY "NOTIFICATIONCENTER_TO_SHAKY"

/**
 *  发送吃到金币通知
 */
#define EAT_GOLD_REWARD_USER "EAT_GOLD_REWARD_USER"
/**
 *  发送吃到能改变猪脚状态的道具
 */
#define EATE_TOOLS_ENEMYSPRITE_USER "EATE_TOOLS_ENEMYSPRITE_USER"
/**
 *  小鬼撞击主角
 */
#define GOST_EMEMY_HIT_ROLE "GOST_EMEMY_HIT_ROLE"
/**
 *  云碰到主角
 *
 */
#define COLOUD_ENEMY_HIT_ROLE "COLOUD_ENEMY_HIT_ROLE"
/**
 *  石头碰到主角
 */
#define BINDER_ENEMY_HIT_ROLE "BINDER_ENEMY_HIT_ROLE"
/**
 *  主角碰到大便
 */
#define SHIT_ENEMY_HIT_ROLE "SHIT_ENEMY_HIT_ROLE"
/**
 *  主角碰到逗比
 */
#define DOU_ENEMY_HIT_ROLE "DOU_ENEMY_HIT_ROLE"
/**
 *  没有影响主角速度
 */
#define NO_CHANGE_ROLE_SPEED -1
/**
 *  默认攻击力
 */
#define ATTCK 25
//=================================================NotificationCenter end=========================================

//=================================================now Tools Type begin=========================================

//=================================================now Tools Type end===========================================

#define PI 3.1415926
#endif /* defined(__heroJump__ConfigUtil__) */

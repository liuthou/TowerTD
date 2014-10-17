#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace ui;
using namespace CocosDenshion;

/******************************** Messages ******************************/
#define GAME_START "game_start"
#define	GAME_OVER "game_over"
#define	GAME_QUIT "game_quit"
#define	GAME_RESTART "game_restart"

#define	MOVE_UP "move_up"
#define	MOVE_DOWN "move_down"
#define	MOVE_LEFT "move_left"
#define	MOVE_RIGHT "move_right"

#define	PLAYER_DIE "player_die"	// 主角死亡消息
#define	PLAYER_MOVE "player_move"
/************************************************************************/

/************************************************************************/
// player's movement direction
typedef enum {
	UP = 0,
	DOWN,
	LEFT,
	RIGHT
} MovementDirection;
/************************************************************************/

/************************************************************************/

#define SCREEN_SIZE Size(320, 480)
#define VSIZE SCREEN_SIZE

#define PLAYER_MOVE_STEP 15
#define PLAYER_SIZE (Size(80, 97) * 0.7f)

#define MAIN_PLANE_ANI_TAG 1001	// 主机的动画tag值

#define TTF_PATH "fonts\\Marker Felt.ttf"

#define PROP_SIZE Size(80, 40)
#define PROP_MOVE_TIME 3
#define PROP_EFFETIVE_TIME 6

#define ENEMY_MOVE_SPEED 100

#define ENEMY_CREATE_FRIQUENCE_TIME 1.60f
#define PROP_CREATE_FRIQUENCE_TIME 5.00f

#define ENEMY_START_DELAY 1.0f
#define PROP_START_DELAY 6.6f
#define SCORE_COUNTING_START_DELAY 3.0f

/************************************************************************/

#define LEFT_DIRECTION_BTN_POS Vec2(50, 50)
#define RIGHT_DIRECTION_BTN_POS Vec2(100, 50)
#define UP_DIRECTION_BTN_POS Vec2(290, 110)
#define DOWN_DIRECTION_BTN_POS Vec2(290, 40)

/************************************************************************/

//tags
#define ENEMY_TAG 10
#define PROP_TAG 9
#define PLAYER_TAG 8

#define SCORELAYERNAME "ScoreLayer"
#define COPTER_MUSIC "copter.mp3" 
#define CLIK_MUSIC "achievement.mp3"
#define GETBOMB_MUSIC "get_bomb.mp3"
#define ABOUTUI_JSON "Aboutus/Aboutus.json"
#define RETURNBUT "returnBtn"

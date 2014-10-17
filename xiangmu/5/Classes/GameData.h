#ifndef __GAMEDATA_H_
#define __GAMEDATA_H_

//地图个数
#define GAME_MAPS_COUNT 12
//时间增长积分
#define TIME_SCORE 1
//积分自动增长间隔时间
#define ADD_SCORE_TIME 0.5
//主角坐标
#define ROLE_POSITION_X 100
#define ROLE_POSITION_Y 185
//背景速度
#define BACKGROUND_SPEED 150
//障碍物攻击力
#define BLOCK_ATTACK 1500
//主角血量
#define ROLE_ALL_HP 1000
//创可贴状态减血系数
#define BOND_DROP_HP 0.5
//主角每秒掉血量
#define ROLE_SCEOND_HP 2
//主角自动掉血时间间隔
#define DORP_HP_TIME 0.02
//血袋加血量
#define BLOOD_ADD_HP 200

//获得主角层
#define GET_ROLE_LAYER dynamic_cast<RoleLayer *>(dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene())->getRoleLayer())
//获得背景层
#define GET_BACKGROUND_LAYER dynamic_cast<BackgroundLayer *>(dynamic_cast<GameScene *>(Director::getInstance()->getRunningScene())->getBackgroundLayer())

//播放音效
#define BACK_GUOUND_MUSIC(FILENAME, AUDIOFLAG) \
	if (AUDIOFLAG)\
	{\
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(FILENAME, true);\
	}

#define EFFECT_MUSIC(FILENAME, AUDIOFLAG) \
	if (AUDIOFLAG)\
	{\
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FILENAME);\
	}

//窗口大小
#define VISIBLE_SIZE Director::getInstance()->getVisibleSize()

//logo
#define LOGO_FILENAME "gamelogo.png"

//退出对话框图片
#define EXIT_BACKGROUND_FILENAME "exitButton.png"
#define EXIT_YESBUTTON_FILENAME "yesButton.png"
#define EXIT_NOBUTTON_FILENAME "noButton.png"

//主角道具
#define ROLE_STATE_PROTECT "bubbleattachment-sheet0.png"
#define ROLE_STATE_BUCKET "bucketattachment-sheet0"
#define ROLE_STATE_BAND "plaster-sheet0.png"

//the image name of role runAction
#define ROLE_RUN_FILENAME "chicken-sheet0"
#define ROLE_JUMP_UP_FILENAME "chicken-jumpUp-sheet0"
#define ROLE_JUMP_DOWN_FILENAME "chicken-jumpDown-sheet0"
#define ROLE_HURT_FILENAME "chicken-hurt-sheet0"
#define ROLE_DIE_FILENAME "chicken-die-sheet0"
#define ROLE_ELECTRIC_FILENAME "chicken-electric-sheet0"
//主角下落素材
#define ROLE_JUMPING_0_FILENAME "chicken-jumpDown-sheet0.png"
#define ROLE_JUMPING_1_FILENAME "chicken-jumpDown-sheet1.png"

//主角死亡掉落素材
#define ROLE_DIEPING_FILENAME "chicken-die-sheet0_01.png"

//开始界面素材
//音效开关
#define AUDIOON_FILENAME "audioon-sheet0.png"
#define AUDIOOFF_FILENAME "audiooff-sheet0.png"
//关于我们界面
#define  ABOUT_FILENAME "about.png"
//开始按钮
#define PLAY_MAIN_1_FILENAME "play_main-sheet0.png"
#define PLAY_MAIN_2_FILENAME "play_main-sheet1.png"
//开始背景
#define MAIN_BACK_FILENAME "main_back-sheet0.png"
//操作提示
#define INSTRUCTIONS_FILENAME "instructions-sheet0.png"
//奖章
#define RIBBON_FILENAME "ribbon-sheet0.png"
//Game Logo
#define GAME_LOGO_FILENAME "headless_logo-sheet0.png"
//Max score
#define MAX_SCORE_FILENAME "kelchend-sheet0.png"

//游戏界面素材
//游戏背景层
//远山
#define L1_S1_FILENAME "l1_s1-sheet0.png"
#define L1_S2_FILENAME "l1_s2-sheet0.png"
//远处的田野
#define L2_S1_FILENAME "l2_s1-sheet0.png"
#define L2_S2_FILENAME "l2_s2-sheet0.png"
//氤氲
#define L3_S1_FILENAME "l3_s1-sheet0.png"
#define L3_S2_FILENAME "l3_s2-sheet0.png"
#define L3_S3_FILENAME "l3_s3-sheet0.png"
//近处的田野
#define L4_S1_FILENAME "l4_s1-sheet0.png"
#define L4_S2_FILENAME "l4_s2-sheet0.png"
#define L4_S3_FILENAME "l4_s3-sheet0.png"
//灌木丛 _BN_ 中的N为1，2，3，4
#define L5_BN_FILENAME "l5_b%d-sheet0.png"
//电线杆、路标 _SN_ 中的N为1，2，3
#define L5_SN_FILENAME "l5_s%d-sheet0.png"
//草丛
#define L7_S1_FILENAME "l7_s1-sheet0.png"
#define L7_S2_FILENAME "l7_s2-sheet0.png"
//路
#define G_S1_FILENAME "g_s1-sheet0.png"
#define G_S2_FILENAME "g_s2-sheet0.png"
#define G_S3_FILENAME "g_s3-sheet0.png"

//显示层
//木框
#define TOPBAR_FILENAME "topbar-sheet0.png"
//暂停按钮
#define PAUSE_BUTTON_1_FILENAME "pausebutton-sheet0.png"
#define PAUSE_BUTTON_2_FILENAME "pausebutton-sheet1.png"
#define SCREEN1BACKTUT "screen1backtut-sheet0.png"
#define SCREEN2BACKTUT "screen2backtut-sheet0.png"
#define MOBILEJUMP "mobilejump-sheet0.png"
#define MOBILE_LEFT "mobile_left-sheet0.png"
#define MOBILE_RIGHT "mobile_right-sheet0.png"
//低血量标志
#define LOW_BLOOD_WARNING "attention-sheet0.png"

//当前分
#define TIMER_FILENAME "timer-sheet0.png"
//条件框
#define CONDITION_NO_FILENAME "a1-sheet0.png"
#define CONDITION_YES_FILENAME "a1-sheet1.png"
//小箭头
#define ARROW_FILENAME "arrow-sheet0.png"

//暂停结束界面
//黑色背景
#define BLACK_BACK_FILENAME "overlay-sheet0.png"
//背景
#define ENDBACK_P_FILENAME "endbackp-sheet0.png"
//暂停LOGO
#define PAUSEGFX_FILENAME "pausegfx-sheet0.png"
//结束LOGO
#define CHICKEN_END_FILENAME "chickenend-sheet0.png"
//新纪录标示
#define NEW_RECORD_FILENAME "newrecord-sheet0.png"
//返回开始界面按钮
#define BACK_P_1_FILENAME "backp-sheet0.png"
#define BACK_P_2_FILENAME "backp-sheet1.png"
//转到帮助界面按钮
#define HOWTOP_1_FILENAME "howtop-sheet0.png"
#define HOWTOP_2_FILENAME "howtop-sheet1.png"
//回到游戏按钮
#define PLAY_P_1_FILENAME "playp-sheet0.png"
#define PLAY_P_2_FILENAME "playp-sheet1.png"
//结束界面重新开始游戏按钮
#define REPLAYER_END_1_FILENAME "replayend-sheet0.png"
#define REPLAYER_END_2_FILENAME "replayend-sheet1.png"
//空按钮或惊险躲避框
#define NEAR_MISS_COLL_FILENAME "near_miss_coll-sheet0.png"

//解锁条件
//达成新纪录
#define CONDITION_1_1_FILENAME "r1-sheet0_04.png"
//游戏次数5次
#define CONDITION_1_2_FILENAME "r1-sheet0_28.png"

//吃到血袋次数
#define CONDITION_2_25_FILENAME "r1-sheet0_17.png"
#define CONDITION_2_50_FILENAME "r1-sheet0_18.png"
#define CONDITION_2_100_FILENAME "r1-sheet0_13.png"
#define CONDITION_2_200_FILENAME "r1-sheet0_01.png"
//吃到血滴次数
#define CONDITION_2_60_FILENAME "r1-sheet0_21.png"
//吃到创可贴次数
#define CONDITION_2_3_FILENAME "r1-sheet0_06.png"

//50分
#define CONDITION_3_10_FILENAME "r1-sheet0_08.png"
#define CONDITION_3_20_FILENAME "r1-sheet0_19.png"
//100分
#define CONDITION_4_10_FILENAME "r1-sheet0_27.png"
#define CONDITION_4_30_FILENAME "r1-sheet0_29.png"

//惊险躲避
#define CONDITION_5_10_FILENAME "r1-sheet0_33.png"
#define CONDITION_5_30_FILENAME "r1-sheet0_32.png"
#define CONDITION_5_50_FILENAME "r1-sheet0_34.png"
#define CONDITION_5_100_FILENAME "r1-sheet0_23.png"

//撞到障碍10次
//夹子
#define CONDITION_6_BEARTRAP_FILENAME "r1-sheet0_02.png"
//火焰
#define CONDITION_6_CAMPFIRE_FILENAME "r1-sheet0_07.png"
//电击
#define CONDITION_6_E_FENCE_FILENAME "r1-sheet0_16.png"
//刀车
#define CONDITION_6_BLADE_FILENAME "r1-sheet0_25.png"

//双倍积分
//获得5次双倍积分道具
#define CONDITION_7_5_FILENAME "r1-sheet0_11.png"
//获得N秒的双倍积分时间
#define CONDITION_7_15_FILENAME "r1-sheet0_14.png"
#define CONDITION_7_30_FILENAME "r1-sheet0_03.png"
#define CONDITION_7_40_FILENAME "r1-sheet0_05.png"
#define CONDITION_7_50_FILENAME "r1-sheet0_26.png"

//最高分500,750,1000,1500,2000,3000,3500
#define CONDITION_8_1_FILENAME "r1-sheet0_10.png"
#define CONDITION_8_2_FILENAME "r1-sheet0_09.png"
#define CONDITION_8_3_FILENAME "r1-sheet0_30.png"
#define CONDITION_8_4_FILENAME "r1-sheet0_20.png"
#define CONDITION_8_5_FILENAME "r1-sheet0_31.png"
#define CONDITION_8_6_FILENAME "r1-sheet0_24.png"
#define CONDITION_8_7_FILENAME "r1-sheet0_12.png"

//达成条件后解锁的道具
//50分
#define TOOLS_SCORE_50_FILENAME "unlocks-sheet0_01.png"
//短时间双倍得分
#define TOOLS_DOUBLE_SCORE_5_FILENAME "unlocks-sheet0_02.png"
//创可贴
#define TOOLS_PLASTER_FILENAME "unlocks-sheet0_03.png"
//初始血量增加20%
#define TOOLS_BEGIN_HP_20_FILENAME "unlocks-sheet0_04.png"
//长时间双倍得分
#define TOOLS_DOUBLESCORE_15_FILENAME "unlocks-sheet0_05.png"
//血滴
#define TOOLS_BLOOD_DROP_FILENAME "unlocks-sheet0_06.png"
//初始血量增加40%
#define TOOLS_BEGIN_HP_40_FILENAME "unlocks-sheet0_07.png"
//100分
#define TOOLS_SCORE_100_FILENAME "unlocks-sheet0_08.png"
//保护罩
#define TOOLS_SHIELD_FILENAME "unlocks-sheet0_09.png"
//水桶
#define TOOLS_BUCKET_FILENAME "unlocks-sheet0_10.png"
//红十字
#define TOOLS_BLOOD_USEABLE_FILENAME "unlocks-sheet0_11.png"
//奖章
#define TOOLS_RIBBON_FILENAME "unlocks-sheet0_12.png"

#endif // !__GAMEDATA_H_

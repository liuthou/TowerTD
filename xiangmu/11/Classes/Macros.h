//
//  Macros.h
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-20.
//
//

#ifndef TexasPoker_Macros_h
#define TexasPoker_Macros_h

/**
 *  定义一个创建场景的宏
 *
 *  @param __TYPE__ 继承与Layer的类
 *
 *  @return 场景
 */
#ifndef CREATE_SCENE(__TYPE__)
#define CREATE_SCENE(__TYPE__)\
static Scene * createScene(){ \
auto _scene = Scene::create(); \
auto _layer = __TYPE__::create(); \
_scene->addChild(_layer); \
return _scene; \
};
#endif


//PokerAction AI的延时操作时间 默认: 2.0f 测试时:0.1f
#define PokerAction_AI_DELAY_TIME 2.0f

//PokerAction 操作结束后的筹码移动速度 默认: 0.5f  测试时:0.1f
#define PokerAction_EndAndRunBetMoverAnimationTime 0.5f

//BetTimePokerAnimation_BETTIME 下注进度条 默认:10.f
#define  BetTimePokerAnimation_BETTIME 10.0f

//DealingPokersAnimation 发牌速度 默认:1000 测试时:5000
#define DealingPokersAnimation_dealMoveTime 1000



#endif // __Macros.h_FILE_END_

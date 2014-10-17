//
//  PlayGameScene.h
//  heroJump
//
//  Created by mazhai on 14-9-16.
// 
//

#ifndef __heroJump__PlayGameScene__
#define __heroJump__PlayGameScene__
/**
 *  add by mabs
 *  主场景、积分层、背景层、添加台阶层、道具层、敌人层、主角层，都添加在这个场景
 
 */
#include <iostream>
#include "cocos2d.h"
#include "ScoreLayer.h"
#include "ToolsLayer.h"
#include "EnemyLayer.h"
#include "RoleLayer.h"
#include "BroadcastLayer.h"
#include "GoldandGemLayer.h"
#include "BackgroundLayer.h"
#include "ChooseToolsLayer.h"
#include "ToolAnimationLayer.h"
USING_NS_CC;
class PlayGameScene:public Scene {
private:
     bool pauseSceneTag;
    void onEnter();
    /**
     *  添加积分层
     */
    void addScoreLayer();
    /**
     *  添加道具层
     */
    void addToolsLayer();
    /**
     *  添加敌人层
     */
    void addEnemyLayer();
    /**
     *  添加主角层
     */
    void addRoleLayer();
    void reloadData();
    /**
     *  添加景高层
     */
    void addInjuredEffect();
    /**
     *  addBroadcastLayer
     */
    void addBroadcastLayer();
    /**
     *  add background
     */
    void addBackgroundLayer();
    /**
     *  添加选择道具层
     */
    void addChangeToolsLayer();

	/************************************************************************/
	/* add role animation                                                   */
	/************************************************************************/
	void addRoleAnimationLayer();
    
    
public:
    virtual bool init();
    CREATE_FUNC(PlayGameScene);
    /**
     *  得到积分层
     *
     *  @return 积分层
     */
    ScoreLayer* getScoreLayer();

	ToolAnimationLayer* getRoleAnimationLayer();
    /**
     *  得到道具层
     *
     *  @return 道具层
     */
    ToolsLayer* getToolsLayer();
    /**
     *  得到敌人层
     *
     *  @return 敌人层
     */
    EnemyLayer* getEnemyLayer();
    /**
     *  得到主角层
     *
     *  @return 主角层
     */
    RoleLayer* getRoleLayer();
    BackgroundLayer * getBackgroundLayer();
	GoldandGemLayer * getGoldangGemLayer();
    ChooseToolsLayer* getChooseToolsLayer();
	void gaiBian();
    
    void pauseSceneMenu();
    void pauseSceneMethod(Ref * sender);
};

#endif /* defined(__heroJump__PlayGameScene__) */

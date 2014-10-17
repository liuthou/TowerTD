//
//  JumpHelp.h
//  heroJump
//
//  Created by mazhai on 14-9-21.
//
//

#ifndef __heroJump__JumpHelp__
#define __heroJump__JumpHelp__
/**
 *  add by mabs
 *  packing static functions
 *
 */
#include <iostream>
#include <cocos2d.h>

#include "PlayGameScene.h"
#include "RoleLayer.h"
#include "ToolsLayer.h"
#include "WoodSprite.h"
#include "ChooseToolsLayer.h"
#include "RoleSprite.h"
USING_NS_CC;
class JumpHelp {
    
    
public:
    /**
     *  get Role
     *
     *  @return RoleSprite*
     */
    static RoleSprite* getRoleSprite();
    /**
     *  get RoleLayer
     *
     *  @return RoleLayer*
     */
    static RoleLayer* getRoleLayer();
    /**
     *  get BackgroundLayer
     *
     *  @return BackgroundLayer*
     */
    static BackgroundLayer* getBackgroundLayer();
    /**
     *  get playGameScene's Scene
     *
     *  @return PlayGameScene*
     */
    static PlayGameScene* getPlayGameScene();
    /**
     *  get ChooseToolsLayer Scene
     *
     *  @return ChooseToolsLayer*
     */
    static ChooseToolsLayer* getChooseToolsLayer();
    /**
     *  get ToolsLayer
     *
     *  @return ToolsLayer*
     */
    static ToolsLayer* getToolsLayer();
    
    /**
     *  get WoodSprite
     *
     *  @return WoodSprite*
     */
    static WoodSprite* getWoodSprite();
    
    /**
     *  jump ation
     *
     *  @param tex   png
     *  @param row
     *  @param cloum
     *
     *  @return Animate*
     */
    
    static Animate* getJumpAnimate(Texture2D *tex,std::vector<Rect> vrs,int start,int end);
   
    static std::vector<Rect> getVec2ByTwoPoint(Vec2 p1,Vec2 p2);
   
    static Animate* getJumpAnimate(Texture2D *tex,std::vector<Rect> vrs,int start,int end,float unit);
    
};

#endif /* defined(__heroJump__JumpHelp__) */

//
//  JumpHelp.cpp
//  heroJump
//
//  Created by mazhai on 14-9-21.
//
//

#include "JumpHelp.h"

PlayGameScene* JumpHelp::getPlayGameScene(){
    return dynamic_cast<PlayGameScene*>(Director::getInstance() -> getRunningScene());
}

RoleLayer* JumpHelp::getRoleLayer(){
    PlayGameScene* playGameScene = getPlayGameScene();
    if (NULL == playGameScene) {
        return NULL;
    }
    RoleLayer *roleLayer = playGameScene -> getRoleLayer();
    return roleLayer;
}
RoleSprite* JumpHelp::getRoleSprite(){
    RoleLayer *roleLayer = getRoleLayer();
    if (NULL == roleLayer) {
        return NULL;
    }
    RoleSprite *roleSprite = dynamic_cast<RoleSprite*>(roleLayer -> getChildByName(ROLE_SPRITE));
    return roleSprite;
}
ChooseToolsLayer* JumpHelp::getChooseToolsLayer(){
    PlayGameScene* playGameScene = getPlayGameScene();
    if (NULL == playGameScene) {
        return  NULL;
    }
    ChooseToolsLayer *chooseToolsLayer = playGameScene -> getChooseToolsLayer();
    return chooseToolsLayer;
}

ToolsLayer* JumpHelp::getToolsLayer(){
    PlayGameScene* playGameScene = getPlayGameScene();
    if (NULL == playGameScene) {
        return NULL;
    }
    ToolsLayer* toolsLayer = playGameScene -> getToolsLayer();
    return toolsLayer;
}


BackgroundLayer* JumpHelp::getBackgroundLayer(){
    PlayGameScene* playGameScene = getPlayGameScene();
    if (NULL == playGameScene) {
        return NULL;
    }
    BackgroundLayer* backGroundLayer = playGameScene -> getBackgroundLayer();
    return backGroundLayer;
}


Animate* JumpHelp::getJumpAnimate(Texture2D *tex,std::vector<Rect> vrs,int start,int end){
    Animation * anim =Animation::create();
    auto ite = vrs.begin();
    ite += start;
    auto endIte = ite + end;
    for (; ite!=endIte; ite ++) {
        anim-> addSpriteFrameWithTexture(tex, *ite);
    }
    
    anim->setDelayPerUnit(0.15);
    anim->setLoops(1);
    
    return Animate::create(anim);
}
Animate* JumpHelp::getJumpAnimate(Texture2D *tex,std::vector<Rect> vrs,int start,int end,float unit){
    Animation * anim =Animation::create();
    auto ite = vrs.begin();
    ite += start;
    auto endIte = ite + end;
    for (; ite!=endIte; ite ++) {
        anim-> addSpriteFrameWithTexture(tex, *ite);
    }
    
    anim->setDelayPerUnit(unit);
    anim->setLoops(1);
    
    return Animate::create(anim);
}

std::vector<Rect> JumpHelp::getVec2ByTwoPoint(Vec2 p1,Vec2 p2){
    std::vector<Rect> spoint;
    float value_y = p2.y - p1.y;
	float value_x = p2.x - p1.x;
    float value = value_y/value_x;
	int i = 1;
	float x = 0,y = 0;
	float distance = abs(p1.x - p2.x);
	for (i = 1 ; i <= distance; i ++)
	{
        if ( value >= 0 )
		{
			x = p1.x + i;
			y = p1.y + value * i;
			if (x >= p2.x)
			{
				break;
			}
		}
		else if(value <= 0)
		{
			
			x = p2.x - i;
			y = p2.y - value * i;
			if (x <= p1.x)
			{
				break;
			}
		}
		spoint.push_back(Rect(x, y, 1, 1));
	}
    return spoint;
}

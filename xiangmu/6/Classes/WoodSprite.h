//
//  WoodSprite.h
//  heroJump
//
//  Created by mazhai on 14-9-20.
//
//

#ifndef __heroJump__WoodSprite__
#define __heroJump__WoodSprite__

#include <iostream>
#include <cocos2d.h>
#include "UseToolsBaseSprite.h"
#include "ConfigUtil.h"
#include "SystemMarcoUtil.h"
#define WOOD_SPEED 9
#define WOOD_REDINS 90
USING_NS_CC;
class WoodSprite : public UseToolsBaseSprite{
private:
    std::vector<Rect> rects;
public:
    virtual bool init();
    virtual void collisionRole();
    virtual void changeRoleState();
    virtual void onEnter();
    CREATE_FUNC(WoodSprite);
    virtual std::string sendCast();
    virtual std::vector<Rect> getRects();
    virtual float getRoleSpeedTime();
    virtual float getRedians();
};
#endif /* defined(__heroJump__WoodSprite__) */

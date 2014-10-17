//
//  UseToolsBaseSprite.h
//  heroJump
//
//  Created by mazhai on 14-9-20.
//
//

#ifndef __heroJump__UseToolsBaseSprite__
#define __heroJump__UseToolsBaseSprite__



#include <iostream>
#include <cocos2d.h>
#include "BodyAbstract.h"
#include "SystemMarcoUtil.h"
USING_NS_CC;
/**
 *  add by mabs
 *  you can pull and drag
 */
class UseToolsBaseSprite:public BodyAbstract {

public:
    virtual bool init();
    
    virtual void die();
    /**
     *  when role collision it
     */
    virtual void collisionRole();
    /**
     *  get this body speed for role
     *
     *  @return SpeedTime
     */
    virtual float getRoleSpeedTime() = 0;
    virtual float getRedians() = 0;
    virtual std::vector<Rect> getRects() = 0;
    virtual std::string sendCast();
    bool isDie;
};

#endif /* defined(__heroJump__UseToolsBaseSprite__) */

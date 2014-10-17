//
//  BodyAbstract.h
//  heroJump
//
//  Created by mazhai on 14-9-20.
//
//

#ifndef __heroJump__BodyAbstract__
#define __heroJump__BodyAbstract__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;


/**
 *  add by mabs
 *  can collision
 */
class BodyAbstract : public Sprite{
    
    
public:
    virtual bool init();
    /**
     *  collision Role and execute action
     */
    virtual void collisionRole() = 0;
    
    virtual std::string sendCast() = 0;
};


#endif /* defined(__heroJump__BodyAbstract__) */

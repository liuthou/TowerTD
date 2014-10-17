//
//  BaseColouds.h
//  herojump
//
//  Created by lanou3g on 14-9-20.
//
//

#ifndef __herojump__BaseColouds__
#define __herojump__BaseColouds__
#include "cocos2d.h"
#include <iostream>
using namespace cocos2d;
class BaseColouds:public Sprite{
public:
    virtual bool initWithFile(std::string fileName,int speed);
     CC_SYNTHESIZE(bool, isDie,Die);
    
};

#endif /* defined(__herojump__BaseColouds__) */

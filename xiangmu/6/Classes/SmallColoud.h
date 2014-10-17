//
//  SmallColoud.h
//  herojump
//
//  Created by lanou3g on 14-9-20.
//
//

#ifndef __herojump__SmallColoud__
#define __herojump__SmallColoud__
#include "cocos2d.h"
#include "BaseColouds.h"
#include <iostream>
#define SMALLCOLOUD_SPEED 70
class SmallColoud:public BaseColouds{
public:
    virtual bool init(int speed);
    static SmallColoud* create(int speed);
};
#endif /* defined(__herojump__SmallColoud__) */

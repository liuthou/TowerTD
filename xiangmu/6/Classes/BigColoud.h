//
//  BigColoud.h
//  herojump
//
//  Created by lanou3g on 14-9-20.
//
//

#ifndef __herojump__BigColoud__
#define __herojump__BigColoud__
#include "cocos2d.h"
#include "BaseColouds.h"
#include <iostream>
#define BIGCOLOUD_SPEED 40
class BigColoud:public BaseColouds{
public:
    virtual bool init(int speed);
    static BigColoud *create(int speed);
};

#endif /* defined(__herojump__BigColoud__) */

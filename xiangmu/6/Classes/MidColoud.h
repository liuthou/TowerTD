//
//  MidColoud.h
//  herojump
//
//  Created by lanou3g on 14-9-20.
//
//

#ifndef __herojump__MidColoud__
#define __herojump__MidColoud__
#include "cocos2d.h"
#include "BaseColouds.h"
#include <iostream>
#define MIDCOLOUD_SPEED 60
class MidColoud:public BaseColouds{
public:
    virtual bool init(int speed);
    static MidColoud *create(int speed);
};
#endif /* defined(__herojump__MidColoud__) */

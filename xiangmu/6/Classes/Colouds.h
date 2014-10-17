//
//  Colouds.h
//  herojump
//
//  Created by lanou3g on 14-9-20.
//
//

#ifndef __herojump__Colouds__
#define __herojump__Colouds__
#include "cocos2d.h"
#include <iostream>
#include "BaseColouds.h"
using namespace cocos2d;
class Colouds{
protected:
    static Colouds * instance;
    
public:
   
    CC_SYNTHESIZE_PASS_BY_REF(Vector<BaseColouds *>, coloudVector, ColoudVector);
    static Colouds * getInstance();
    void addColoud(BaseColouds * coloud);
    void deleteColoud();
    void reset();
};

#endif /* defined(__herojump__Colouds__) */

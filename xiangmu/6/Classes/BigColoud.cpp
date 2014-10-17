//
//  BigColoud.cpp
//  herojump
//
//  Created by lanou3g on 14-9-20.
//
//

#include "BigColoud.h"
bool BigColoud::init(int speed){
    if (!BaseColouds::initWithFile("yun1.png", speed)) {
        return false;
    }
    
    return true;
}
BigColoud *BigColoud::create(int speed){
    auto big = new BigColoud();
    if (big && big->init(speed)) {
        big->autorelease();
        return big;
    }
    CC_SAFE_DELETE(big);
    return nullptr;
}
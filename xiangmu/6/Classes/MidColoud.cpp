//
//  MidColoud.cpp
//  herojump
//
//  Created by lanou3g on 14-9-20.
//
//

#include "MidColoud.h"
bool MidColoud::init(int speed){
    if (!BaseColouds::initWithFile("yun5.png", speed)) {
        return false;
    }
    
    return true;
}
MidColoud *MidColoud::create(int speed){
    auto mid = new MidColoud();
    if (mid && mid->init(speed)) {
        mid->autorelease();
        return mid;
    }
    CC_SAFE_DELETE(mid);
    return nullptr;
}
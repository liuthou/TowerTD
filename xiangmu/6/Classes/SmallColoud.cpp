//
//  SmallColoud.cpp
//  herojump
//
//  Created by lanou3g on 14-9-20.
//
//

#include "SmallColoud.h"
bool SmallColoud::init(int speed){
    if (!BaseColouds::initWithFile("yun1.png", speed)) {
        return false;
    }
    
    return true;
}
SmallColoud *SmallColoud::create(int speed){

    return nullptr;
}
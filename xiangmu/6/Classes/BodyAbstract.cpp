//
//  BodyAbstract.cpp
//  heroJump
//
//  Created by mazhai on 14-9-20.
//
//

#include "BodyAbstract.h"
bool BodyAbstract::init(){
    if (!Sprite::init()) {
        return false;
    }
    return true;
}

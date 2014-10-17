//
//  Colouds.cpp
//  herojump
//
//  Created by lanou3g on 14-9-20.
//
//

#include "Colouds.h"
Colouds * Colouds::instance = nullptr;
Colouds * Colouds::getInstance(){
    if (!instance) {
        instance = new Colouds();
    }
    return instance;
}
void Colouds::addColoud(BaseColouds * coloud){
    coloudVector.pushBack(coloud);
}
void Colouds::deleteColoud(){
    for (auto it = coloudVector.begin(); it != coloudVector.end();) {
        if ((*it)->getDie()) {
            it =  coloudVector.erase(it);
        }else{
            it++;
        }
    }
}
void Colouds::reset(){
    coloudVector.clear();
}
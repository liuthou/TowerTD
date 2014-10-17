//
//  Hall.cpp
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-13.
//
//

#include "Hall.h"

#include "Room.h"

using namespace TexasPoker;

bool Hall::init(){
    if (!Layer::init()) {
        return false;
    }
	//数据初始化
	this->ID = 1;	
	this->ScoreMin = 5;
	this->ScoreLimit = 10;

    joinRoom();
	/*for (int i=1; i<11; i++) {
	Rooms.insert(i, new Room(i,ScoreLimit,ScoreMin));
	}*/
    
    return true;
}

Hall::~Hall(){
    
}

void Hall::createRoom(HallType hType){
    if (hType == HallType::CHINA) {
        auto scene = Room::createScene(1,2000,10);
        Director::getInstance()->replaceScene(scene);
    }
}

void Hall::createRoom(){

}

void Hall::joinRoom(){
    
}

void Hall::joinRoom(int roomID){
    
}



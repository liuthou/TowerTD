#ifndef __GAMEBASIC_H
#define __GAMEBASIC_H
#include "cocos2d.h"
#include "cocoStudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
 using namespace CocosDenshion;
using namespace cocos2d;
using namespace ui;
using namespace cocostudio;

//level data
#define MAXLEVEL 24
#define TOWERNUMBER 8
//tower data
#define FPS 60
#define TOWERONECOST 100
#define TOWERTWOCOST 150
#define TOWERTHREECOST 200
#define TOWERFORECOST 350
#define TOWERFIVECOST 400
#define TOWERSIXCOST 300
#define TOWERSEVENCOST 500
#define TOWEREIGHTCOST 350
//skill data
#define SKILLSPEED 550.0f
#define ARROWATK 20.0f
#define BIGARROWATK 80.0f
#define THUNDERSKILL 20.0f/60.0f //pre second
#define DOUBLETHUNDER 40.0f/60.0f
#define YELLOWTHUNDER 60.0f/60.0f
#define FIRESKILL 60.0f
#define ICESKILL 50.0f
#define WINDSKILL 50.0f/60.0f
#define BONESKILL 80.0f
//superskill type

#endif // !__GAMEBASIC_H

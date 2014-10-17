//
//  EnemyLayer.h
//  heroJump
//
//  Created by mazhai on 14-9-17.
//
//

#ifndef __heroJump__EnemyLayer__
#define __heroJump__EnemyLayer__

#include <iostream>
#include "cocos2d.h"
#define FILENAMESHIT "li.jpg"
#define FILENAMEICE "11.png"
#define FILENAMECLOUD "yun5.png"
#define FILENAMEDOU "dou.jpg"
#define FIRSTOUTTIME 0
#define FIRSTOUTTOOLS 0.8
#define FIRSTTIME 0
#define FIRSTDIETOOLPERCENT 3
#define FIRSTNOTDIETOOLPERCENT 20
#define FIRSTLEVELT 20
#define ENDDIETOOLPERCENT 10
#define ENDNOTDIETOOLPERCENT 50
#define ENDOUTTOOLTIME 0.2
USING_NS_CC;
class EnemyLayer:public Layer {
protected:
    int m_Toolsnumber;
	Size vSize;
	Size pSize;
	float outTimeSum;
	float outTools;
	int dieTool;
	int notDieTool;
	float t;
	unsigned long levelt;
public:
	//come nextLevel
	void nextLevel();
	//add time
	void addTime(float t);
	/*
	 *Ö¡»Øµ÷£¬Ò»Ö±³ö¹Ö
	 */
	void update(float t);
	/*
	 *¿ªÊ¼³ö¹Ö£»
	 */
	void go();
	void onEnter();
    virtual bool init();
    CREATE_FUNC(EnemyLayer);
};
#endif /* defined(__heroJump__EnemyLayer__) */

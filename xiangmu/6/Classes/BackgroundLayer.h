//
//  BackgroundLayer.h
//  heroJump
//
//  Created by mazhai on 14-9-17.
//
//

#ifndef __heroJump__BackgroundLayer__
#define __heroJump__BackgroundLayer__
#include <iostream>
#include "cocos2d.h"


#define BG1 "bg2.png"
#define BG2 "bg2.png"
#define BG3 "bg2.png"
#include "JumpParameter.h"
#define DIE_CONDITAINS winsize.height * 3/ 4
USING_NS_CC;
class BackgroundLayer:public Layer {
private:
    void deleteAllToolsFun(float ft);
protected:
    Size winsize;
    Size bgsize;
    int bigCloudProbablity;
    int midout;
    int smallout;
    int quickMoveSpeed;
    float upLength;
    float midLength;
    float roleMoveDownLength;
    //float finalLength;
    JumpParameter *jumpParameter;
    float everyTimeLength;
    float leftTime;
    float allTime;
    float moveDownSpeed;
    float v0_Down;
    float vt_Down;
    float v0_Up;
    float vt_Up;
    __NotificationCenter* center;
    
    void update(float t);
    void addUpLayer();
    void addMidLayer();
    void addDownLayer();
    void addToolLayer(Layer *layer);
public:
    Layer * upLayer;
    Layer * midLayer;
    Layer * downLayer;
    Layer * currMidLayer;
    Layer * currUpLayer;
    Layer * currDownLayer;
    Label * curScoreLabel;
    
    CC_SYNTHESIZE(float, finalLength, FinalLength);
    virtual bool init();
    CREATE_FUNC(BackgroundLayer);
    void cloudsAppear(float t);
    void checkWeatherOverTheLimited();
    virtual void onEnter();
    
//    void die();
    void align(Ref * sender);
    void stopScheduleMethed(Ref * sender);
    void startScheduleMethed(Ref * sender);
    void bgMoveDown(Ref * sender);
    void TestSchedul(float t);
    void addScore();
    void backgroundShaky(Ref * sender);
    
    void addEatGoldScore(Ref* sender);
    void gameOver(Ref* sender);
    Sprite *test;
};
#endif /* defined(__heroJump__BackgroundLayer__) */

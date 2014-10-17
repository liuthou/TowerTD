//
//  MainScene.h
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-26.
//
//

#ifndef __TexasPoker__MainScene__
#define __TexasPoker__MainScene__

#include <iostream>
#include <cocos2d.h>


#include "cocostudio/CocoStudio.h"
#include "Macros.h"
#include <ui/CocosGUI.h>
USING_NS_CC;
using namespace ui;
using namespace cocostudio;

#include <cocos-ext.h>
using namespace extension;

class MainScene : public Layer{
public:
    CREATE_FUNC(MainScene);
    CREATE_SCENE(MainScene);
private:
    Button * endterRoom;
    void onTouchButton(Ref*ref,ui::Widget::TouchEventType type);

    virtual bool init();
    virtual void initUI();
    void initAudio();
    
    virtual void onEnter();
    virtual void onExit();
    
    /**
     初始化卡片
     */
    void initButtonBG();
    Menu * cardMenu;
    MenuItemImage *card1Bg;
    Label * card1Label;
    Sprite * card1Sprite;
    void onMenu1(Ref * ref);
    
    MenuItemImage *card2Bg;
    Label * card2Label;
    Sprite * card2Sprite;
    
    MenuItemImage *card3Bg;
    Label * card3Label;
    Sprite * card3Sprite;
    
    void initCityIcon();
    MenuItemSprite * PreButton;
    MenuItemSprite * NextButton;
    
};
#endif /* defined(__TexasPoker__MainScene__) */

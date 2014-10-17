//
//  LoginScene.h
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-26.
//
//

#ifndef __TexasPoker__LoginScene__
#define __TexasPoker__LoginScene__

#include <iostream>
#include <cocos2d.h>


#include "Macros.h"
#include "cocostudio/CocoStudio.h"
#include <ui/CocosGUI.h>
USING_NS_CC;
using namespace ui;
using namespace cocostudio;

class LoginScene : public Layer{
public:
    void SinglePlay();
    CREATE_FUNC(LoginScene);
    CREATE_SCENE(LoginScene);
private:
    
    Button * singleButton;
    Button * weixinButton;
    Button * weiboButton;
    Button * qqButton;
    
    void onTouchButton(Ref*ref,ui::Widget::TouchEventType type);
    
    virtual bool init();
    virtual void initUI();
    virtual void onExit();
};

#endif /* defined(__TexasPoker__LoginScene__) */

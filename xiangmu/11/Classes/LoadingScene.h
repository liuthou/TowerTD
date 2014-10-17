//
//  LoadingScene.h
//  TexasPoker
//
//  Created by 袁文龙 on 14-9-26.
//
//

#ifndef __TexasPoker__LoadingScene__
#define __TexasPoker__LoadingScene__

#include <iostream>
#include <cocos2d.h>


#include "Macros.h"
#include "cocostudio/CocoStudio.h"
#include <ui/CocosGUI.h>
USING_NS_CC;
using namespace cocostudio;
using namespace ui;

class LoadingScene : public Layer{
public:
    CREATE_FUNC(LoadingScene);
    CREATE_SCENE(LoadingScene);
private:
    float processValue;
    Text * processLabel;
    LoadingBar * processBar;
    
    void onProcess(Texture2D* t2d);
    
    virtual bool init();
    virtual void initUI();
    void initAudio();
    
    virtual void onEnter();
    
    void loadPNG();
    void loadPlist();
    void loadScene();
};
#endif /* defined(__TexasPoker__LoadingScene__) */

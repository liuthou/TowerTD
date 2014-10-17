//
//  LoadingScene.h
//  CarrotFantasy
//
//  Created by Yan on 14-10-3.
//
//

#ifndef __CarrotFantasy__LoadingScene__
#define __CarrotFantasy__LoadingScene__

#include "cocos2d.h"
using namespace cocos2d;

class GameScene;

class LoadingScene:public Scene
{
public:
    
    CREATE_FUNC(LoadingScene);
    
protected:
    
    virtual bool init()override;
    
    virtual void onEnter()override;
    
    virtual void onExit()override;
    
    virtual void sourceLoadCallBack(Ref *pData);
    
protected:
    
    GameScene *_pGameScene = nullptr;

};

#endif /* defined(__CarrotFantasy__LoadingScene__) */

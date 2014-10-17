//
//  WelcomeScene.h
//  newCardDefence
//
//  Created by Yan on 14-8-27.
//
//

#ifndef __newCardDefence__WelcomeScene__
#define __newCardDefence__WelcomeScene__

#include "PublicDefine.h"

class WelcomeScene:public Scene
{
    
public:
    
    CREATE_FUNC(WelcomeScene);
    
    virtual ~WelcomeScene();
    
protected:
    
    virtual bool init();
    
    virtual void onEnter()override;
    
    virtual void showMenu();

private:
    
    Layer *_pSpritesLayer = nullptr;
    
    Layer *_pMenusLayer = nullptr;

};

#endif /* defined(__newCardDefence__WelcomeScene__) */

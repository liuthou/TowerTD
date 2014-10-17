//
//  LevelSelectScene.h
//  newCardDefence
//
//  Created by Yan on 14-9-12.
//
//

#ifndef __newCardDefence__LevelSelectScene__
#define __newCardDefence__LevelSelectScene__

#include "SceneBase.h"

class LevelSelectScene: public SceneBase
{
public:
    
    CREATE_FUNC(LevelSelectScene);
    
    virtual ~LevelSelectScene();
    
protected:
    
    virtual bool init();
    
    virtual void onEnter()override;
    
private:
    
    int _iThemeIndex = 0;
    
    Layer *_pLevelSelectLayer = nullptr;
};

#endif /* defined(__newCardDefence__LevelSelectScene__) */

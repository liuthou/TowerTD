//
//  LevelSelectLayer.h
//  newCardDefence
//
//  Created by Yan on 14-9-10.
//
//

#ifndef __newCardDefence__LevelSelectLayer__
#define __newCardDefence__LevelSelectLayer__

#include "PublicDefine.h"

class LevelSelectLayer: public Layer
{
public:

	CREATE_FUNC(LevelSelectLayer);
    
    virtual ~LevelSelectLayer();
    
protected:
    
    virtual bool init();
    
    virtual void loadSource();
    
    virtual void loadLevel();
    
    virtual void loadMenuItem();
    
    virtual std::tuple<int, bool> checkLevelIsLockAndBarrierIsClean(const int &rILevelIndex);
    
    virtual void changeToGameScene();
    
    virtual void loadData();

    
private:
    
    int _iPageIndex = 0;
    
    int _iCurLevelIndex = 0;
    
    ValueMap _DataValueMap;
    
private:
    
    Sprite *_pLockSprite = nullptr;
    
    MenuItemSprite *_pStartBtn = nullptr;
};

#endif /* defined(__newCardDefence__LevelSelectLayer__) */

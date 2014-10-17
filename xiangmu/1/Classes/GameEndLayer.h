//
//  GameEndLayer.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-30.
//
//

#ifndef __CarrotFantasy__GameEndLayer__
#define __CarrotFantasy__GameEndLayer__

#include "PublicDefine.h"

class GameEndLayer: public Layer
{
    
public:
    
    static GameEndLayer *create(const GameEndType &rEnGameEndType);
    
protected:
    
    virtual bool init(const GameEndType &rEnGameEndType);
    
    virtual void createMenu();
    
    virtual void loadInfo();
    
    virtual void onEnter()override;
    
    virtual void onExit()override;
    
    virtual void registerNoTouch();
    
    virtual void saveLevelData();
    
    virtual void playGameEndSound();
    
    virtual void checkCarrotType();
    
private:
    
    GameEndType _enGameEndType = en_GameWin;
    
    int _iCarrotType = 0;
    
    std::string _sCarrotType = "";
    
};

#endif /* defined(__CarrotFantasy__GameEndLayer__) */

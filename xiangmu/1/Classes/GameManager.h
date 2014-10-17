//
//  GameManager.h
//  CarrotFantasy
//
//  Created by Yan on 14-10-4.
//
//

#ifndef __CarrotFantasy__GameManager__
#define __CarrotFantasy__GameManager__

#include "PublicDefine.h"

class GameManager:public Ref
{
public:

    CREATE_INSTANCE_FUNC(GameManager);
    
    DESTROY_INSTANCE_FUNC();
    
protected:
    
    virtual bool init();
    
    CC_SYNTHESIZE_PASS_BY_REF(int, _iCarrotHp, ICarrotHp);
    
    CC_SYNTHESIZE_PASS_BY_REF(int, _iMonsterBatch, IMonsterBatch);
    
    CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsPause, IsPause);
    
private:
    
    GameManager(){}
    
    GameManager(const GameManager&) = delete;
    
    GameManager &operator=(const GameManager&) = delete;
    
};

#endif /* defined(__CarrotFantasy__GameManager__) */

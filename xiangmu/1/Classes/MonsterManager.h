//
//  MonsterManager.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __CarrotFantasy__MonsterManager__
#define __CarrotFantasy__MonsterManager__


#include "PublicDefine.h"

class Entity;

class MonsterManager: public Ref
{
public:
    
    CREATE_INSTANCE_FUNC(MonsterManager);
    
    DESTROY_INSTANCE_FUNC();
    
    virtual MonsterVec &getMonsterVec();
    
    virtual void setFuncAddMonsterToLayer(const std::function<void (Entity*)> &rFuncAddMonsterToLayer);
    
    virtual void clearManager();
    
    virtual void clearBeAtkLockState();
    
protected:
    
    friend class MonsterBase;
    
    virtual void openCheckGameEnd(Ref *pSender);
    
    virtual void addMonster(MonsterBase *pBullet);
    
    virtual bool init();
    
    virtual void registerDeadEvent();
    
    virtual void removeMonsterFromManager(Ref *pMonster);
    
private:
    
    MonsterVec *_pMonsterVec = nullptr;
    
    std::function<void (Entity *)> _funcAddMonsterToLayer;
    
    bool _bIsOpenCheckGameEnd = false;
    
private:
    
    MonsterManager();
    
    virtual ~MonsterManager();
    
    MonsterManager(const MonsterManager & ) = delete;
    
    MonsterManager &operator=(const MonsterManager &) = delete;
    
};


#endif /* defined(__CarrotFantasy__MonsterManager__) */

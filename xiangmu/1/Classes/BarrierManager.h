//
//  BarrierManager.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __CarrotFantasy__BarrierManager__
#define __CarrotFantasy__BarrierManager__

#include "PublicDefine.h"

class Entity;

class BarrierManager: public Ref
{
public:

    CREATE_INSTANCE_FUNC(BarrierManager);
    
    DESTROY_INSTANCE_FUNC();
    
    BarrierVec &getBarrierVec();
    
    virtual void setFuncAddBarrierToLayer(const std::function<void (Entity*)> &rFuncAddBarrierToLayer);
    
    virtual void clearBeAtkLockState();
    
    virtual void clearManager();
    
protected:
    
    friend class BarrierBase;
    
    virtual void addBarrier(BarrierBase *pBarrier);
    
    virtual bool init();
    
    virtual void registerBarrierDeadEvent();
    
    virtual void removeBarrierFromManager(Ref *pBarrier);
    
private:
    
    BarrierVec *_pBarrierVec = nullptr;
    
    std::function<void (Entity*)> _funcAddBarrierToLayer;
    
private:
    
    BarrierManager();
    
    virtual ~BarrierManager();
    
    BarrierManager(const BarrierManager &) = delete;
    
    BarrierManager &operator=(const BarrierManager &) = delete;
};

#endif /* defined(__CarrotFantasy__BarrierManager__) */

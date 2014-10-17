//
//  BulletManager.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __CarrotFantasy__BulletManager__
#define __CarrotFantasy__BulletManager__

#include "PublicDefine.h"
class Entity;
class BulletManager: public Ref
{
public:
    
    CREATE_INSTANCE_FUNC(BulletManager);
    
    DESTROY_INSTANCE_FUNC();
    
    virtual BulletVec &getBulletVec();
    
    virtual void setFuncAddBulletLayer(const std::function<void (Entity*)> &rFuncAddBulletLayer);
    
    virtual void checkBulletIsDead();
    
    virtual void clearManager();
    
protected:
    
    friend class BulletBase;
    
    virtual void addBullet(BulletBase *pBullet);
    
    virtual bool init();
    
private:
    
    BulletVec *_pBulletVec = nullptr;
    
    std::function<void (Entity*)> _funcAddBulletLayer;
    
private:
    
    BulletManager();
    
    virtual ~BulletManager();
    
    BulletManager(const BulletManager & ) = delete;
    
    BulletManager &operator=(const BulletManager &) = delete;
    
};

#endif /* defined(__CarrotFantasy__BulletManager__) */

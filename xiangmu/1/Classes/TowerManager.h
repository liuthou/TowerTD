//
//  TowerManager.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __CarrotFantasy__TowerManager__
#define __CarrotFantasy__TowerManager__

#include "PublicDefine.h"

class Entity;

class TowerManager:public Ref
{
public:
    
    CREATE_INSTANCE_FUNC(TowerManager);
    
    DESTROY_INSTANCE_FUNC();
    
    virtual TowerVec &getTowerVec();
    
    virtual void setFuncAddTowerLayer(const std::function<void (Entity*)> &rFuncAddEntityLayer);
    
    virtual void clearManager();

	virtual void setFuncCheckMoney(const std::function<int()> &rFuncCheckMoney);

	virtual int getMoney();
protected:
    
    friend class TowerBase;

    virtual void addTower(TowerBase *pTower);
    
    virtual void registerTowerDeadEvent();
    
    virtual bool init();
    
    virtual void removeTowerFromManager(Ref *pSender);
    
private:
    
    TowerVec *_pTowerVec = nullptr;

    std::function<void (Entity*)> _funcAddTowerToLayer;

	std::function<int()> _funcCheckMoney;

    
private:
    
    TowerManager();
    
    virtual ~TowerManager();
    
    TowerManager(const TowerManager & ) = delete;
    
    TowerManager &operator=(const TowerManager &) = delete;
    
};


#endif /* defined(__CarrotFantasy__TowerManager__) */

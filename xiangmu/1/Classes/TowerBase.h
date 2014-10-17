//
//  TowerBase.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __CarrotFantasy__TowerBase__
#define __CarrotFantasy__TowerBase__

#include "Entity.h"

class VictimEntityBase;


class TowerBase:public Entity
{
public:
    
	static TowerBase* create(const int &rId);
	
	/**
	*  Tower rocate
	*/
	virtual void doRocation(float dt);

    virtual ~TowerBase();
	
	virtual int getTowerGradeCost();

	/**
	*  set current atk target
	*
	*  @param pVictimEntity target point
	*/
	virtual void setAtkTarget(VictimEntityBase *pVictimEntity);

	virtual void showGradeMark();

	virtual void hideGradeMark();

	/**
	*  check target is in atk range
	*
	*  @param rPos atk pos
	*
	*  @return in range return true ,other return false
	*/
	virtual bool isInAtkRange(const Vec2 &rPos);
	/**
	*  upGrade Tower
	*/
	virtual void upGrade();
protected:
    /**
     *  deadAction func
     */
    virtual void deadAction(const std::string &rSDeadImageFile = "")override;
    /**
     *  check atk target
     *
     *  @param rDt frame num
     */
    virtual void checkAtkTarget(float dt);
    /**
     *  choose Atk target
     */
    virtual void chooseAtkTarget();
    /**
     *  check lock target is out of atk range
     */
    virtual void checkTargetIsOutOfRange();
    /**
     *  miss Atr Target
     */
    virtual void missAtkTarget();
	/**
	*  Tower fire
	*/
	virtual void fire(float dt);
	/**
	*  init the Tower
	*/
	virtual void initTower();
    
    virtual bool init(const int &rId);
    /**
     *  Tower fire func
     */
	virtual void fireAction();
    /**
     *  Tower relative Bullet Name
     */
    CC_SYNTHESIZE_PASS_BY_REF(int, _iBulletId, IBulletId);
    /**
     *  Tower' Atk speed, equal Bullet speed
     */
    CC_SYNTHESIZE_PASS_BY_REF(int, _iAtkRange, IAtkRange);
    /**
     *  Tower' Atk Space
     */
    CC_SYNTHESIZE_PASS_BY_REF(double, _iAtkSpace, IAtkSpace);
    /**
     *  Tower need cost number which that upgrade
     */
    CC_SYNTHESIZE_PASS_BY_REF(std::string, _sUpgradeCost, SUpgradeCose);
    /**
     *  Tower Atk, Speed, Range, Space and cost be add which that upgrade
     */
    CC_SYNTHESIZE_PASS_BY_REF(int, _iUpgradeCount, IUpgradeCount);
    /**
     *  is rotation
     */
    CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsRotation, BIsRotation);
	/**
	 *  Tower CreateCost
	 */
	CC_SYNTHESIZE_PASS_BY_REF(int, _iCreateCost, ICreateCost);
    
    /**
     *  have atk Target 
     */
    CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsHaveAtkTarget, IsHaveAtkTarget);
	
protected:
	Sprite* _pGradeMark = nullptr;
	/**
	 *  tower panel
	 */
	Sprite *_pTowerPanel = nullptr;
	/*
     *  effect atk target
     */
    VictimEntityBase *_pAtkTarget = nullptr;
};

#endif /* defined(__CarrotFantasy__TowerBase__) */

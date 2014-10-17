//
//  VictimBase.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-15.
//
//

#ifndef __CarrotFantasy__VictimEntityBase__
#define __CarrotFantasy__VictimEntityBase__

#include "Entity.h"
class HpSlot;

class VictimEntityBase:public Entity
{
public:
    
    virtual ~VictimEntityBase();
    
    /**
     *  Entity beHurt and run beHurt(param) func
     *
     *  @param rBeHurtValue is Atk value
     */
    virtual void beHurt(const AtkProperty tBeHurtValue);
    
    virtual void setAtkTarget(const bool &rBisAtkTarget);
    
    virtual bool getAtkTarget()const {return _bIsAtkTarget;};
    
    virtual void hpSlotVisible(const bool &rBIsVisible);
    
protected:
    
    virtual void closeHpSlot(float dt);
    
	virtual void checkAtkTarget(float dt);
    
    virtual bool init(const int &rIId, const std::string &rSCsvFileName);
    
    virtual void createLockFlagAnimate();
    /**
     *  bind hp Slot sprite
     */
    virtual void createHpSlotSprite();
    /**
     *  bind lock Atk Target sprite
     */
    virtual void createLockAtkSprite();
    /**
     *  deadAction func
     */
    virtual void deadAction(const std::string &rSDeadImageFile = "")override;
    /**
     *  beHurtAction abstract func use child
     */
    virtual void behurtAction() = 0;
    /**
     *  barrier and monster has hp property
     */
    CC_SYNTHESIZE_PASS_BY_REF(int, _iHp, IHp);
	/**
	*  monster state
	*/
	CC_SYNTHESIZE_PASS_BY_REF(int, _iState, IState);
	/**
	 * state Duration
	 */
	CC_SYNTHESIZE_PASS_BY_REF(float, _fSlowDuration, FSlowDuration);
	CC_SYNTHESIZE_PASS_BY_REF(float, _fStopDuration, fStopDuration);
	CC_SYNTHESIZE_PASS_BY_REF(float, _fPoisonDuration, fPoisonDuration);

	CC_SYNTHESIZE_PASS_BY_REF(float,_iBulletStateType,IBulletStateType);
    /**
     *  Hp Slot close time
     */
    const int _iHpCloseTime = 3;
    
private:
    
    bool _bHpSlotExsit = false;
    
    /**
     *  hp slot sprite
     */
    HpSlot *_pHpSlot = nullptr;
    /**
     *  LockAtk flag sprite
     */
    Sprite *_pLockAtkTarget = nullptr;
    /**
     *  lock flag animation
     */
    Animate *_pLockFlagAnimate = nullptr;
    
    /**
     *  flag Victim is be Atk target
     */
    bool _bIsAtkTarget = false;
	
    Vec2 _Pos;
    
    Size _Size;
};

#endif /* defined(__CarrotFantasy__VictimBase__) */

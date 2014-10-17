//
//  MonsterBase.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#ifndef __CarrotFantasy__MonsterBase__
#define __CarrotFantasy__MonsterBase__

#include "VictimEntityBase.h"
#include "DynamicPropertyInterFace.h"

class MoveControllerBase;

class MonsterBase: public VictimEntityBase, public DynamicPropertyInterFace
{
	friend class MonsterFactory;
    
public:
    /**
     *  monster create with id
     */
	static MonsterBase * create(const int &rIId);

	void setMaxSpeed(const int &iSpeed);

protected:
    /**
     *  deadAction func
     */
    virtual void deadAction(const std::string &rSDeadImageFile = "")override;
    /**
	 * only make modle sprite do Action
	 */
    virtual void doAction(const float &rDt);
	/**
	*  monster init
	*/
    virtual bool init(const int &rIId);
    /**
     *  behurt Action
     */
    virtual void behurtAction();
	/**
	 * create move Animation
	 */
	virtual void createAnimation();
	/**
	 * Monster sound
	 */
	virtual void MonsterSound();
    /**
     *  judge Monster direction
     */
    CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsLeft, IsLeft);

	MoveControllerBase * _pMoveController = nullptr;
};

#endif /* defined(__CarrotFantasy__MonsterBase__) */

//
//  BulletBase.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//
#ifndef __CarrotFantasy__BulletBase__
#define __CarrotFantasy__BulletBase__

#include "Entity.h"
#include "DynamicPropertyInterFace.h"

class BulletBase:public Entity, public DynamicPropertyInterFace
{

public:
	std::set<int>& getIdMap();
	
	virtual void doMove();

	static BulletBase *create(const int &rIId, VictimEntityBase *rVictimEntity);
    /**
     *  bullet move func
     */

	virtual AtkProperty getAtkPro();
    
    virtual void deadAction(const std::string &rSDeadImageFile = "");
    
    /**
     *  animation
     *
     *  @param rDt delay time
     */
    virtual void doAction(const float &rDt);
    
protected:

	virtual bool init(const int &rId, VictimEntityBase *rVictimEntity);
    /**
     *  if Tower is defence type, so bullet have sub speed effect
     */
    CC_SYNTHESIZE_PASS_BY_REF(int, _iAtkState, IAtkState);

	CC_SYNTHESIZE_PASS_BY_REF(int, _iBulletType, IBulletType);

	CC_SYNTHESIZE_PASS_BY_REF(int, _iDeadActCount, IDeadActCount);

	VictimEntityBase *_pAtkTarget = nullptr;

	std::set<int> *_IdMap = nullptr;
};

#endif /* defined(__CarrotFantasy__BulletBase__) */
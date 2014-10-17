//
//  DynamicPropertyInterFace.h
//  CarrotFantasy
//
//  Created by Yan on 14-9-19.
//
//

#ifndef __CarrotFantasy__DynamicPropertyInterFace__
#define __CarrotFantasy__DynamicPropertyInterFace__

#include "PublicDefine.h"

class DynamicPropertyInterFace
{
public:
    
    virtual ~DynamicPropertyInterFace();

protected:
    
    virtual void createDynamicEntityAnimation(const std::vector<std::string> &rAnimationFiles);
    
    virtual bool init(const int &rId, const std::string &rSCsvFileName);
    /**
     *  move and move Action
     */
    virtual void doAction(const float &rDt) = 0;
    /**
     *  Dynamic Entity speed
     */
    CC_SYNTHESIZE_PASS_BY_REF(unsigned int, _iSpeed, ISpeed);
    /**
     *  Bullet' Atk
     */
    CC_SYNTHESIZE_PASS_BY_REF(int, _iAtk, IAtk);
    
protected:
    
	Animation * _pAnimation = nullptr;
    
};

#endif /* defined(__CarrotFantasy__DynamicEntityBase__) */

//
//  CCShake.h
//  heroJump
//
//  Created by mazhai on 14-10-4.
//
//

#ifndef __heroJump__CCShake__
#define __heroJump__CCShake__

#include <iostream>
#include <cocos2d.h>
class CCShake : public cocos2d::ActionInterval
{
    // Code by Francois Guibert
    // Contact: www.frozax.com - http://twitter.com/frozax - www.facebook.com/frozax
public:
    CCShake();
    
    // Create the action with a time and a strength (same in x and y)
    static CCShake* create(float d, float strength );
    // Create the action with a time and strengths (different in x and y)
    static CCShake* createWithStrength(float d, float strength_x, float strength_y );
    bool initWithDuration(float d, float strength_x, float strength_y );
    virtual CCShake * reverse() const override;
	virtual CCShake *clone() const override;
protected:
    
    void startWithTarget(cocos2d::Node *pTarget);
    void update(float time);
    void stop(void);
    
    
    // Initial position of the shaked node
    float m_initial_x, m_initial_y;
    // Strength of the action
    float m_strength_x, m_strength_y;
};
#endif /* defined(__heroJump__CCShake__) */

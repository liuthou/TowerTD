//
//  CCShake.cpp
//  heroJump
//
//  Created by mazhai on 14-10-4.
//
//

#include "CCShake.h"
#include "cocos2d.h"
USING_NS_CC;

// not really useful, but I like clean default constructors
CCShake::CCShake() : m_strength_x(0), m_strength_y(0), m_initial_x(0), m_initial_y(0)
{
}

CCShake* CCShake::create( float d, float strength )
{
    // call other construction method with twice the same strength
    return createWithStrength( d, strength, strength );
}

CCShake* CCShake::createWithStrength(float duration, float strength_x, float strength_y)
{
    CCShake *pRet = new CCShake();
    
    if (pRet && pRet->initWithDuration(duration, strength_x, strength_y))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    
    return pRet;
}
CCShake * CCShake::reverse() const
{
    // FIXME: This conversion isn't safe.
    return (CCShake*)ReverseTime::create(const_cast<CCShake*>(this));
}
CCShake* CCShake::clone() const

{
    
    // no copy constructor
    
    auto a = new CCShake();
    
    a->autorelease();
    
    return a;
    
}

bool CCShake::initWithDuration(float duration, float strength_x, float strength_y)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_strength_x = strength_x;
        m_strength_y = strength_y;
        return true;
    }
    
    return false;
}

// Helper function. I included it here so that you can compile the whole file
// it returns a random value between min and max included
static float fgRangeRand( float min, float max )
{
    float rnd = ((float)rand()/(float)RAND_MAX);
    return rnd*(max-min)+min;
}

void CCShake::update(float dt)
{
    float randx = fgRangeRand( -m_strength_x, m_strength_x )*dt;
    float randy = fgRangeRand( -m_strength_y, m_strength_y )*dt;
    
    // move the target to a shaked position
    _target->setPosition( Vec2(Vec2(m_initial_x, m_initial_y)+Vec2( randx, randy)));
}

void CCShake::startWithTarget(Node *pTarget)
{
    CCActionInterval::startWithTarget( pTarget );
    
    // save the initial position
    m_initial_x = pTarget->getPosition().x;
    m_initial_y = pTarget->getPosition().y;
}

void CCShake::stop(void)
{
    // Action is done, reset clip position
    this->getTarget()->setPosition( Vec2( m_initial_x, m_initial_y ) );
    
    CCActionInterval::stop();
}
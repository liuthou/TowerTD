#pragma once
#include "cocos2d.h"
USING_NS_CC;

class BaseSprite : public Sprite{
public:
	CC_SYNTHESIZE(PhysicsBody *, m_body, M_body);
	CC_SYNTHESIZE(std::string, m_name, M_name);
	CC_SYNTHESIZE(std::string, m_type, M_type);
protected:
	virtual bool init(std::string fileName);
};
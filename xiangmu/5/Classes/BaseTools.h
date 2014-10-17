#ifndef __BASETOOLS__H
#define __BASETOOLS__H
#include "cocos2d.h"
#include "BaseSprite.h"
USING_NS_CC;

enum State
{
	Tool_protected			= 1,		//保护罩
	Tool_doubleScore		= 1 << 1,	//双倍积分
	Tool_goldDoubleScore	= 1 << 2,	//金牌双倍积分
	Tool_bucket				= 1 << 3,	//水桶
	Tool_band				= 1 << 4,	//创可贴
	Tool_addBlood			= 1 << 5,	//血袋加血
	Tool_addBloodMost		= 1 << 6,	//血滴加血
	Tool_addScore			= 1 << 7,	//加五十分
	Tool_addScoreMost		= 1 << 8	//加一百分
};

class BaseTools : public BaseSprite
{
public:
	static BaseTools * create(std::string fileNameStr, int state, std::string m_name);
	virtual bool init(std::string fileNameStr, int state, std::string m_name);
	void removeBaseTool();
	void addPhysicsBody();
	CC_SYNTHESIZE_READONLY(int, m_state, M_state);
protected:
	
};

#endif
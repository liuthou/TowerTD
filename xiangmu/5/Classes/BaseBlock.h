#ifndef _BASEBLOCK_H_
#define _BASEBLOCK_H_
#include "cocos2d.h"
#include "BaseSprite.h"
USING_NS_CC;

//class of base block 障碍物基类
class BaseBlock : public BaseSprite
{
protected:
	virtual bool init(std::string fileNameStr, float attack, std::string name, Vec2 blockPos);
	//添加刚体
	virtual void addPhysicsBody();
	//如果是刀，添加动画
	virtual void addKnifeAction();
	//如果是铁链，运行动画
	virtual void addChainhookAction(Vec2 blockPos);
public:
	CC_SYNTHESIZE_READONLY(int, m_attack, M_attack);
	static BaseBlock * create(std::string fileNameStr, float attack, std::string name, Vec2 blockPos);
};

#endif // !_BASEBLOCK_H_

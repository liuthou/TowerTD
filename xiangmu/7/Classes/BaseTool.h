/************************************************************************/
/* 
	道具类型
	产生位置
	dieRunAnimation()死亡动画
	runAnimation()运行动画

	重写create 方法
	init

*/
/************************************************************************/
#ifndef __BASETOOL_H_
#define __BASETOOL_H_

#include "cocos2d.h"
#include "RoleAnimate.h"

using namespace cocos2d;

typedef enum 
{
	ADDSCORE = 1,				//分数
	ADDBLOOD,				//血量
	ADDRANGE,				//射程
	ADDATTACK,				//攻击力
	ADDSPEED				//速度
}ToolsType;

class BaseTool:public Sprite{

protected:
	//道具类型
	CC_SYNTHESIZE(ToolsType,m_type,M_type);
	CC_SYNTHESIZE(int,m_score,M_score);
public:
	
	virtual bool initWithSpriteFrameName(Vec2 position);
	static BaseTool *create(Vec2 position);
	//void runAnimation(std ::string fileName);			//运行动画
	void remove();				//移除道具

};


#endif

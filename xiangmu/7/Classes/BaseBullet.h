/************************************************************************/
/* 
需要实现的功能：
		属性：
				1.m_attack  攻击力
				2.m_range   射程
				3.die()     死亡
				4.move()    移动
				5.m_state  状态（状态不同发射不同的子弹）

*/
/************************************************************************/
#ifndef __BASEBULLET_H_
#define __BASEBULLET_H_

#include "cocos2d.h"

using namespace cocos2d;

class BaseBullet:public Sprite{

protected:
	CC_SYNTHESIZE(int,m_range,M_range);		//   射程
	Size m_vsize;		//可视区大小
public:
	
	virtual bool init(std::string fileName);
	static BaseBullet * create(std::string fileName);
	virtual void die();			// 死亡
	void move();		//   移动	
	CC_SYNTHESIZE_PASS_BY_REF(bool,m_state,State);

};

#endif
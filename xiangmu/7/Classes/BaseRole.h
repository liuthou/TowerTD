/************************************************************************/
/* 
需要实现的功能：
		1.继承自 Sprite
		2.属性：
				m_hp//血量
				move()移动   虚函数
				m_speed速度
				m_attack攻击了（主角的攻击力为0）
				jump()跳  虚函数
				hurt()    虚函数
				die()   死亡  虚函数
				bornAnimate() 出生动画  虚函数
				dieRunAnimation()死亡动画    虚函数  通过子类传过给基类照片来做死亡动画

			
*******************************************************************/

#ifndef __BASEROLE_H_
#define __BASEROLE_H_

#include "cocos2d.h"

using namespace cocos2d;

class BaseRole:public Sprite{

protected:
	int m_hp;					//血量
	int m_speed;				//速度
	int m_attack;					//攻击了（主角的攻击力为0）
	CC_SYNTHESIZE_PASS_BY_REF(bool,m_state,State);				//设置状态


public:
	virtual bool initWithSpriteFrameName(std::string fileName);
	static BaseRole *create(std::string fileName);
		
		void move();					//移动   虚函数
		
		void jump();						//跳  虚函数
		void hurt();					// 虚函数
		void die();					  //死亡  虚函数
		void bornAnimate();				// 出生动画  虚函数
		void dieRunAnimation(const char *fileNames,...);				//死亡动画    虚函数  通过子类传过给基类照片来做死亡动画

		void remove();			//在屏幕移除
};

#endif

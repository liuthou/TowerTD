#ifndef __ROLE__H
#define __ROLE__H
#include "cocos2d.h"
#include "BaseSprite.h"
USING_NS_CC;

enum RoleState
{
 	Role_protected			= 1,		//保护罩
 	Role_doubleScore		= 1 << 1,	//双倍积分
 	Role_goldDoubleScore	= 1 << 2,	//金牌双倍积分
 	Role_bucket				= 1 << 3,	//水桶
 	Role_band				= 1 << 4,	//创可贴
 	Role_addBlood			= 1 << 5,	//血袋加血
 	Role_addBloodMost		= 1 << 6,	//血滴加血
 	Role_addScore			= 1 << 7,	//加五十分
 	Role_addScoreMost		= 1 << 8	//加一百分
};

class Role : public BaseSprite
{
public:
	CREATE_FUNC(Role);
	void changeState(int);

	//主角的各种运动及其停止
	void normalRun();
	void slowRun();
	void fastRun();
	void jumpUp();
	void stopFastRun();
	void stopSlowRun();

	//控制主角下降的行为
	void moveY(float t);

	void hurt(int attack, bool isEfence);
	void die();
	
	CC_SYNTHESIZE_READONLY(int, m_hp, M_hp);
protected:
	virtual ~Role();
	virtual bool init();
	void update(float t);
	void addPhysicsBody();
	void dropHpByTime(float t);
	void boundaryDetection(float t);
	void addSprite();
	void addParticle();
private:
	bool bostZoneFlag;
	//音效开关
	int audioFlag;
	//主角飙血效果
	ParticleSystemQuad * quickBlood;
	ParticleSystemQuad * slowBlood;
	//判断主角是否在下降
	bool isJumpingDown;

	//主角前进或后退的速度
	int moveSpeed;

	//主角的运动状态
	bool isFastRun;
	bool isSlowRnu;
	bool isNormalRun; 
	bool isRunning;

	//主角的属性
	int m_state;
	
	//道具
	Sprite * protect;
	Sprite * band;
	Sprite * bucket;

	//主角的各种动画
	Animate * normalRunAction;
	Animate * slowRunAction;
	Animate * fastRunAction;
	Animate * jumpUpAction;
	Animate * hurtAction;
	Animate * electricAction;
};

#endif
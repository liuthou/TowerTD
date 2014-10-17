#ifndef _SKILLBULLET_H
#define _SKILLBULLET_H

#include "LinearBullet.h"
#define  TIME 3
enum SkillStyle
{
	ray = 1,
	storage
};
class SkillBullet : public BaseBullet{
protected:
	
public:
	CC_SYNTHESIZE(std::string,_fileName,FileName);
	CC_SYNTHESIZE(float, _bulletLevel, BulletLevel);
	CC_SYNTHESIZE(Vec2,_point_Skill,Point_Skill);
	virtual bool init(Vec2 fromPosition, float attack, std::string fileName, int skillstyle, int level);
	static SkillBullet *create(Vec2 fromPosition, float attack, std::string fileName, int skillstyle, int level);
	void create_Sprite(float t);
	void create_Storage(float t);
	virtual void onEnter();
	virtual void die();
};
#endif
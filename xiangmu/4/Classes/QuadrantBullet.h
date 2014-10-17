#ifndef _QUADRANTBULLET_H_
#define _QUADRANTBULLET_H_

#include "BaseBullet.h"

class QuadrantBullet : public BaseBullet{
protected:
	Vec2 toPosition;
	void exeQuadrantBullet(Vec2 fromPosition);
public:
	virtual bool init(float speed, Vec2 fromPosition, float attack, std::string fileName, Vec2 toPosition, int bulletSpecies);
	static QuadrantBullet *create(float speed, Vec2 fromPosition, float attack, std::string fileName, Vec2 toPosition, int bulletSpecies);
	virtual void onEnter();
};
#endif

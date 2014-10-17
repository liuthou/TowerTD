#ifndef _LINEARBULLET_H_
#define _LINEARBULLET_H_
#include "cocos2d.h"
using namespace cocos2d;
#include "BaseBullet.h"

class LinearBullet : public BaseBullet{
protected:
public:
	virtual bool init(float speed, Vec2 fromPosition, float attack, std::string fileName,int bulletSpecies,int pro);
	static LinearBullet *create(float speed, Vec2 fromPosition, float attack, std::string fileName, int bulletSpecies, int pro);
	virtual void onEnter();
};
#endif
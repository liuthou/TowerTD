#ifndef __MONSTERLAYER_H
#define __MONSTERLAYER_H
#include "cocos2d.h"
using namespace cocos2d;
class MonsterLayer :public Layer
{
private:
	bool _oneBoss;
	std::string _fileName;
	void createMonster(float t);
public:
	virtual bool init(std::string filename);
	static MonsterLayer *create(std::string filename);
	void stopUnschedu();
	MonsterLayer():_oneBoss(false){}
	~MonsterLayer();
};

#endif
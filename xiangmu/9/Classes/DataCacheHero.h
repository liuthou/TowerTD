#ifndef __DATACACHEHERO_R_
#define __DATACACHEHERO_R_

#include "cocos2d.h"
#include "string.h"
using namespace cocos2d;

class DataCacheHero : public Ref
{
private:
	DataCacheHero(){}
	DataCacheHero(const DataCacheHero & dataCacheHero){}
	DataCacheHero operator + (const DataCacheHero & dataCacheHero)
	{
	   return dataCacheHero;
	}
	static DataCacheHero * instance;
public:
	static DataCacheHero * getInstance();
	CC_SYNTHESIZE(int, _id, Id);	
	CC_SYNTHESIZE(int, _hpValue, HpValue);
	CC_SYNTHESIZE(int, _mpValue, MpValue);	
	CC_SYNTHESIZE(int, _spValue, SpValue);
	CC_SYNTHESIZE(int, _expValue, ExpValue);	
	CC_SYNTHESIZE(int, _levelValue, LevelValue);
	CC_SYNTHESIZE(int, _attackValue, AttackValue);
	CC_SYNTHESIZE(int, _nowExpValue, NowExpValue);
	CC_SYNTHESIZE(int, _needExpValue, NeedExpValue);
	CC_SYNTHESIZE(double, _agilityValue, AgilityValue);
	CC_SYNTHESIZE(double, _defenseValue, DefenseValue);
	 void setName(char * name)
	{
		_name = new char();
		strcpy(_name,name);
	}
	char * getName()
	{
	    return _name;
	}
	 void setIntroduce(char * introduce)
	{
		_introduce = new char();
		strcpy(_introduce,introduce);
	}
	char * getIntroduce()
	{
	    return _introduce;
	}
private:
	char * _name;
	char * _introduce;
};

#endif
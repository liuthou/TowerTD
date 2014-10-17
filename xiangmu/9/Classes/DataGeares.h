#ifndef __DATAGEARES_R_
#define __DATAGEARES_R_

#include "cocos2d.h"
#include "DataCacheGear.h"
using namespace cocos2d;

class DataGeares
{
private:
	static DataGeares * instance;
public:
	static DataGeares * getInstance();
	void addGearRef(DataCacheGear * gear);
	//存放技能数据的容器
	CC_SYNTHESIZE_PASS_BY_REF(Vector<DataCacheGear *>, _dataGeares,DataGeares);
private:
	DataGeares(){}
	DataGeares(const DataGeares & skilles){}
	DataGeares operator = (const DataGeares & dataGeares)
	{
		return dataGeares;
	}
	//清除容器中的所有元素
	void clearDataGeares();
};

#endif
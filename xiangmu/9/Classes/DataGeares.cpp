#include "DataGeares.h"

DataGeares * DataGeares::instance = NULL;

DataGeares * DataGeares::getInstance()
{
	if(instance == NULL)
	{
		instance = new DataGeares();
	}
	return instance;
}

void DataGeares::addGearRef(DataCacheGear * gear)
{
	_dataGeares.pushBack(gear);
}

void DataGeares::clearDataGeares()
{
	_dataGeares.clear();
}
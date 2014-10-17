#include "DataCacheHero.h"

DataCacheHero * DataCacheHero::instance = NULL;

DataCacheHero * DataCacheHero::getInstance()
{
	if(instance == nullptr){
		instance = new DataCacheHero();
	}
	return instance;
}
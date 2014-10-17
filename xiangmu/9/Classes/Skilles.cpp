#include "Skilles.h"

Skilles * Skilles::instance = NULL;

Skilles * Skilles::getInstance()
{
	if(instance == NULL)
	{
		instance = new Skilles();
	}
	return instance;
}

void Skilles::addSkillRef(DataCacheSkill * skill)
{
	_skilles.pushBack(skill);
}

void Skilles::clearSkilles()
{
	_skilles.clear();
}
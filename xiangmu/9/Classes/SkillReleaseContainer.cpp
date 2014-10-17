#include "SkillReleaseContainer.h"

SkillReleaseContainer * SkillReleaseContainer::instance = NULL;

SkillReleaseContainer * SkillReleaseContainer::getInstance()
{
	if(instance == NULL)
   {
	   instance = new SkillReleaseContainer();
   }
	return instance;
}

void SkillReleaseContainer::addSkillRelease(SkillBase * skill)
{
	_skillCreate.pushBack(skill);
}
void SkillReleaseContainer::removeSkill()
{

	for(auto x = _skillCreate.begin(); x != _skillCreate.end();)
	{	
		if((*x)->getIsDie())
		{
		   x = (_skillCreate).erase(x);
	    }
		else
		{
		   x++;
		}
	}
}
void SkillReleaseContainer::clearContainer()
{
	_skillCreate.clear();
}


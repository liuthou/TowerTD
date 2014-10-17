#include "SwordmanHero.h"
#include "HeroMacro.h"
#include "DataCacheHero.h"
#include "DataGeares.h"

bool SwordmanHero::init()
{
	if(!HeroBase::initWithSpriteFrameName(HERO_RUN_0))
	{
		return false;
	}
	DataCacheHero * dataCacheHero = DataCacheHero::getInstance();
	//人物属性的读取
	_id = dataCacheHero->getId();
	_hpValue = dataCacheHero->getHpValue();
	_allHp = _hpValue;
	_mpValue = dataCacheHero->getMpValue();
	_allMp = _mpValue;
	_attackValue = dataCacheHero->getAttackValue();
	_attackBaseValue = _attackValue;
	_practicalAttackValue = _attackValue;
	_defenseValue = dataCacheHero->getDefenseValue();
	_agilityValue = dataCacheHero->getAgilityValue();
	_expValue = dataCacheHero->getExpValue();
	_nowExpValue = dataCacheHero->getNowExpValue();
	_levelValue = dataCacheHero->getLevelValue();
	_needExp = dataCacheHero->getNeedExpValue();
	_spValue = dataCacheHero->getSpValue();
	addHeroAttribute();
	return true;
}

void SwordmanHero::addHeroAttribute()
{
	DataGeares * dataGeares = DataGeares::getInstance();
	for(auto x = dataGeares->getDataGeares().begin(); x != dataGeares->getDataGeares().end(); x++)
	{
		if((*x)->getGearType() == WEAPON && (*x)->getHeroAdorn() == YES)
		 {
			 _attackGearValue = (*x)->getAttickValue();
			 _practicalAttackValue = _attackValue + _attackGearValue;
		 }
		if((*x)->getGearType() == ARMOUR && (*x)->getHeroAdorn() == YES)
		{
			_defenseGearValue = (*x)->getDefenseValue();
		}
		if((*x)->getGearType() == SHOE && (*x)->getHeroAdorn() == YES)
		{
			_agilityGearValue = (*x)->getAglityValue();
		}
	}
}

SwordmanHero::SwordmanHero()
{
	_attackGearValue = 0;
	_defenseGearValue = 0;
	_agilityGearValue = 0;
}

SwordmanHero::~SwordmanHero()
{

}
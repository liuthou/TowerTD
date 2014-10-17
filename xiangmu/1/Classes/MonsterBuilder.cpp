#include "MonsterBuilder.h"
#include "MapUtil.h"
#include "MonsterFactory.h"
#include "MonsterManager.h"
#include "LevelConfigUtil.h"
#include "MonsterBase.h"
#include "GameManager.h"
#include "SoundUtil.h"

bool MonsterBuilder::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Node::init());
		_iBuildNumber = 10;
		_fDelayTime = _iConstDelayTime;
		_MonsterCount = 0;
		_MonsterBuilderNumber = 0;
		_bDelay = true;
		_iNumber = 0;
		_iBatch = 0;
        GameManager::getInstance()->setIMonsterBatch(0);

		_createMonsterAnimation = Animation::create();
		_createMonsterAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mcm01.png"));
		_createMonsterAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mcm02.png"));
		_createMonsterAnimation->setDelayPerUnit(0.15);
		_createMonsterAnimation->setLoops(1);
		_createMonsterAnimation->retain();

		_iReadFileMonsterCount = LevelConfigUtil::getInstance()->getCurLevelMonsterBatchCount();
	
		this->setPosition(MapUtil::getInstance()->getMovePoses().at(0) + Vec2(40,-15));
		
		bRet = true;
	} while (0);
	return bRet;
}

void MonsterBuilder::onEnter()
{
	Node::onEnter();
	schedule(schedule_selector(MonsterBuilder::createMonsterUpdate),1.5,20001,3);
}

void MonsterBuilder::createMonsterUpdate(float t)
{
	if (_MonsterBuilderNumber == 10*_iReadFileMonsterCount)
	{
        SoundUtil::getInstance()->playEffect(FINALWAVE);
		this->unschedule(schedule_selector(MonsterBuilder::createMonsterUpdate));
        NOTIFY->postNotification("openCheckGameEnd");
	}
	if (_fDelayTime < _iConstDelayTime && MonsterManager::getInstance()->getMonsterVec().size() == 0)
	{
		_fDelayTime += t;
	}
	else if (_fDelayTime >= _iConstDelayTime)
	{
        _iBatch = _MonsterBuilderNumber/10 + 1;
        GameManager::getInstance()->setIMonsterBatch(_iBatch);
		NOTIFY->postNotification("monsterBatchChange",(Ref *)&_iBatch);
		MonsterFactoryController();
		_MonsterCount++;
		_MonsterBuilderNumber++;
		if (_MonsterCount == 10)
		{
			_fDelayTime = 0;
			_MonsterCount = 0;
		}
	}
}

void MonsterBuilder::MonsterFactoryController()
{
    SoundUtil::getInstance()->playEffect(BUILDMONSTER);
	if (_iNumber == 10)_iNumber = 0;
	int number = 10 - (_iBatch - 1) * 2;
	MonsterBase * pMonster;
	if (_iBatch == _iReadFileMonsterCount && _iNumber == 5)
	{
		pMonster = MonsterFactory::createMonster(en_Boss_Big);
	}
	else
	{
		if (_iNumber < number)
		{
			pMonster = MonsterFactory::createMonster(MonsterType(1 + int(_iBatch / 5)));
		}
		else
		{
			pMonster = MonsterFactory::createMonster(MonsterType(4 + int(_iBatch / 5)));
		}
	}
	pMonster->setIHp(pMonster->getIHp() + (_iBatch - 1) / 5 * pMonster->getIHp());
	pMonster->setMaxSpeed(pMonster->getISpeed() + int(_iBatch / 5) * 10);
	pMonster->getSprite()->runAction(Animate::create(_createMonsterAnimation));
	_iNumber++;
}

int MonsterBuilder::getBatch()
{
	return _iBatch;
}

MonsterBuilder::~MonsterBuilder()
{
	CC_SAFE_RELEASE_NULL(_createMonsterAnimation);
}
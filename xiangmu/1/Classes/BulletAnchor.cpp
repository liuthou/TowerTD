#include "BulletAnchor.h"
#include "VictimEntityBase.h"
#include "MonsterManager.h"
#include "MonsterBase.h"
#include "BarrierManager.h"
#include "BarrierBase.h"
#include "GameScene.h"



bool BulletAnchor::init(const int & rId, VictimEntityBase *rVictimEntity)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!BulletBase::init(rId, rVictimEntity));

		bRet = true;
	} while (0);
	return bRet;
}

BulletAnchor * BulletAnchor::create(const int & rId, VictimEntityBase *rVictimEntity)
{
	BulletAnchor * pBullet = new BulletAnchor();
	if (pBullet && pBullet->init(rId, rVictimEntity))
	{
		pBullet->autorelease();
		return pBullet;
	}
	CC_SAFE_DELETE(pBullet);
	return nullptr;
}

void BulletAnchor::doAction()
{
	getSprite()->runAction(RepeatForever::create(RotateBy::create(0.7, 360)));
}

void BulletAnchor::doMove(){

	if (_pAtkTarget->getIsDead())
	{
		removeFromParent();
		setIsDead(true);
		return;
	}
	doAction();

	Animation * pAnimation = Animation::create();
	for (int i = 1; i < 7; i++)
	{
		std::string SpriteFrameName = StringUtils::format("PAnchor-1%d.png", i);
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
	}
	pAnimation->setDelayPerUnit(0.05);
	pAnimation->setLoops(1);

	auto deadActionCF = CallFunc::create([=](){
	auto BarrierVector = BarrierManager::getInstance()->getBarrierVec();
	auto  size = BarrierVector.size();
		if (size > 0)
		{
			int num1 = rand() % size;
			int num2 = rand() % size;
			int num3 = rand() % size;

			auto barrierPoint = (BarrierVector.at(num1))->getPosition();
			auto barrierPoint1 = (BarrierVector.at(num1))->getPosition();
			auto barrierPoint2 = (BarrierVector.at(num2))->getPosition();
			auto barrierPoint3 = (BarrierVector.at(num3))->getPosition();

			MoveTo * move1 = MoveTo::create(2.5f, barrierPoint1);
			MoveTo * move2 = MoveTo::create(2.0f, barrierPoint2);
			MoveTo * move3 = MoveTo::create(1.5f, barrierPoint3);
			RotateBy * rotate1 = RotateBy::create(0.05f, 30);
			RotateBy * rotate2 = RotateBy::create(0.05f, 35);
			RotateBy * rotate3 = RotateBy::create(0.05f, 25);
			RepeatForever * rep1 = RepeatForever::create(rotate1);
			RepeatForever * rep2 = RepeatForever::create(rotate2);
			RepeatForever * rep3 = RepeatForever::create(rotate3);


			std::string SpriteFrameName = StringUtils::format("PAnchor%d2.png", getILevel());
			SpriteFrame * fileName = SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName);
			auto Anchor1 = Sprite::createWithSpriteFrame(fileName);
			auto Anchor2 = Sprite::createWithSpriteFrame(fileName);
			auto Anchor3 = Sprite::createWithSpriteFrame(fileName);
			auto layer = Director::getInstance()->getRunningScene()->getChildByTag(1);

			if (getILevel() == 1)
			{
				Anchor1->setPosition(_pAtkTarget->getPosition());
				layer->addChild(Anchor1);

				auto dieCf = CallFunc::create([=](){
					BarrierVector.at(num1)->beHurt(getAtkPro());
					Anchor1->removeFromParentAndCleanup(true);
				});
				Anchor1->runAction(rep1);		
				Anchor1->runAction(Sequence::create(move1, Animate::create(pAnimation),dieCf, NULL));					
			}
			if (getILevel() == 2)
			{
				Anchor1->setPosition(_pAtkTarget->getPosition());
				layer->addChild(Anchor1);
				Anchor2->setPosition(_pAtkTarget->getPosition());
				layer->addChild(Anchor2);

				auto dieCf1 = CallFunc::create([=](){
					BarrierVector.at(num1)->beHurt(getAtkPro());
					Anchor1->removeFromParentAndCleanup(true);
				});
				auto dieCf2 = CallFunc::create([=](){
					BarrierVector.at(num2)->beHurt(getAtkPro());
					Anchor2->removeFromParentAndCleanup(true);
				});
				Anchor1->runAction(rep1);
				Anchor2->runAction(rep2);
				Anchor1->runAction(Sequence::create(move1, Animate::create(pAnimation), dieCf1, NULL));
				Anchor2->runAction(Sequence::create(move2, Animate::create(pAnimation), dieCf2, NULL));
			}
			if (getILevel() == 3)
			{
				Anchor1->setPosition(_pAtkTarget->getPosition());
				layer->addChild(Anchor1);
				Anchor2->setPosition(_pAtkTarget->getPosition());
				layer->addChild(Anchor2);
				Anchor3->setPosition(_pAtkTarget->getPosition());
				layer->addChild(Anchor3);

				auto dieCf1 = CallFunc::create([=](){
					BarrierVector.at(num1)->beHurt(getAtkPro());
					Anchor1->removeFromParentAndCleanup(true);
				});
				auto dieCf2 = CallFunc::create([=](){
					BarrierVector.at(num2)->beHurt(getAtkPro());
					Anchor2->removeFromParentAndCleanup(true);
				});
				auto dieCf3 = CallFunc::create([=](){
					BarrierVector.at(num3)->beHurt(getAtkPro());
					Anchor3->removeFromParentAndCleanup(true);
				});
				Anchor1->runAction(rep1);
				Anchor2->runAction(rep2);
				Anchor3->runAction(rep3);
				Anchor1->runAction(Sequence::create(move1, Animate::create(pAnimation), dieCf1, NULL));
				Anchor2->runAction(Sequence::create(move2, Animate::create(pAnimation), dieCf2, NULL));
				Anchor3->runAction(Sequence::create(move3, Animate::create(pAnimation), dieCf3, NULL));
			}
		}
		
		Rect rect = Rect(_pAtkTarget->getPositionX() - 100, _pAtkTarget->getPositionY() - 100, 200, 200);
		for (auto mIter = MonsterManager::getInstance()->getMonsterVec().begin(); mIter != MonsterManager::getInstance()->getMonsterVec().end(); mIter++)
		{
			MonsterBase * pMonster = (MonsterBase *)(*mIter);
			if (rect.intersectsRect(pMonster->getBoundingBox()))
			{
				pMonster->beHurt(getAtkPro());
			}
			if (pMonster->getIHp() <= 0 || pMonster->getIsDead())
			{
				break;
			}
		}
		for (auto bIter = BarrierManager::getInstance()->getBarrierVec().begin(); bIter != BarrierManager::getInstance()->getBarrierVec().end(); bIter++)
		{
			BarrierBase * pBarrier = (BarrierBase *)(*bIter);
			if (rect.intersectsRect(pBarrier->getBoundingBox()))
			{

				pBarrier->beHurt(getAtkPro());
			}
			if (pBarrier->getIHp() <= 0 || pBarrier->getIsDead())
			{
				break;
			}
		}
		deadAction(_sName);

	});

	Vec2 MovetoPosition = _pAtkTarget->getPosition() - this->getPosition();
	float MoveDistance = this->getPosition().distance(_pAtkTarget->getPosition());
	getSprite()->runAction(Sequence::create(MoveBy::create(MoveDistance / _iSpeed, MovetoPosition), Animate::create(pAnimation), deadActionCF, NULL));

}

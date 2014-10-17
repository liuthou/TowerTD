#include "CollideManage.h"
#include "GameMainScene.h"

bool CollideManage::init()
{
	if(!Layer::init())
	{
	    return false;
	} 
	_boundingBox = BoundingBox::create();
	manageContainer();
	return true;
}

void CollideManage::onEnter(){
	Layer::onEnter();
	auto scene = dynamic_cast<GameMainScene*>(Director::getInstance()->getRunningScene());
	auto layer = scene->getChildByName("heroLayer");
	_hero = (HeroBase*)layer->getChildByTag(100);
	_skillReleaseContainer = SkillReleaseContainer::getInstance();
	_monsterVector = Monsters::getInstance();
}

void CollideManage::manageContainer()
{
	//检测碰撞及容器
	schedule(schedule_selector(CollideManage::containerUpdate),0);
}

void CollideManage::containerUpdate(float t)
{
	//技能释放容器的管理
	skillReleaseContainerManger();
	//装备容器管理
	monsterContainerManger();
	//主角和怪物碰撞,怪物受伤和人物受伤
	heroAttackAndMonsterBounding();
	//技能和怪物的碰撞
	heroSkillBounding();
}

void CollideManage::heroAttackAndMonsterBounding(){
	auto mV = _monsterVector->getMonsterVector();
	Vec2 heroWordPoint = _hero->getParent()->convertToWorldSpace(_hero->getPosition());
	for (auto monster = mV.begin(); monster!= mV.end();monster++)
	{
		Vec2 monsterWordPoint = (*monster)->getParent()->convertToWorldSpace((*monster)->getPosition());
		if (_boundingBox->conductBoundingBox(heroWordPoint, _hero->getContentSize().width/2,monsterWordPoint, (*monster)->getContentSize().width/2) && 
			(_hero->getDirectionTypeWrite() == 7 && _hero->getAttackState() || _hero->getDirectionTypeWrite() == 2 && _hero->getJumpAttackState()))
		{   
		    if((_hero->getDirectionRunTypeWrite() == LEFT && (monsterWordPoint.x < heroWordPoint.x)) || (_hero->getDirectionRunTypeWrite() == RIGHT && (monsterWordPoint.x > heroWordPoint.x)))
		    {
		        (*monster)->monsterHurt(_hero->getAttackValue());
		     }
		}
		//人物受伤
		if (_boundingBox->conductBoundingBox(heroWordPoint, _hero->getContentSize().width/2,monsterWordPoint, (*monster)->getContentSize().width/2) && (*monster)->getMonsterAttackState())
		{
			_hero->heroHurt((*monster)->getAttackValue());
			(*monster)->setMonsterAttackState(false);
		}
	}
	_hero->setAttackState(false);
	_hero->setJumpAttackState(false);
}

void CollideManage::heroSkillBounding(){
	auto skills = _skillReleaseContainer->getSkillCreate();
	auto mV = _monsterVector->getMonsterVector();
	for (auto  skill =skills.begin(); skill!=skills.end(); skill++)
	{	
		for (auto mon = mV.begin(); mon !=mV.end(); mon++)
		{  
			SkillBase * heroSkill = dynamic_cast<SkillBase *>(*skill);
			MonsterBase *monster = dynamic_cast<MonsterBase *>(*mon);
			if(monster->getMonsterDie())
			{
				continue;
			}
			Vec2 skillWordPoint = heroSkill->getParent()->convertToWorldSpace(heroSkill->getPosition());
			Vec2 monWordPoint = monster->getParent()->convertToWorldSpace(monster->getPosition());
			if (_boundingBox->conductBoundingBox(skillWordPoint, heroSkill->getContentSize().width/2, monWordPoint, monster->getContentSize().width/2))
			{
				_skillTime++;
				if(_skillTime > 10)
				{
					_skillTime = 0;
				   monster->monsterHurt(heroSkill->getAttack());
				}
			}
		}
	}

}

void CollideManage::skillReleaseContainerManger()
{
    _skillReleaseContainer->removeSkill();
}
void CollideManage::monsterContainerManger()
{
	_monsterVector->clearMonster();
}
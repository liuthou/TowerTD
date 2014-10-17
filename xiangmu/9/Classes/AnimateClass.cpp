#include "AnimateClass.h"
#include "HeroMacro.h"

 bool AnimateClass::init()
{
	return true;
 }

 ActionInterval *AnimateClass::heroRun()
 {
	Animation *run = Animation::create();
	for (int i = 0; i < 4;i++)
	{
		std::string filename = StringUtils::format("hero_run%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		run->addSpriteFrame(frame);
	}
	run->setDelayPerUnit(0.15);
	run->setLoops(-1);
	auto ami = Animate::create(run);
	return ami;
 }

 ActionInterval *AnimateClass::heroAttack()
 {
	 Animation *heroAttackAnimate = Animation::create();
	 for (int i = 0; i < 3; i++)
	 {
		 std::string filename = StringUtils::format("hero_attick%d.png", i);
		 auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		 heroAttackAnimate->addSpriteFrame(frame);
	 }
     std::string filename1 = StringUtils::format("hero_attick0.png");
	 auto frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename1);
	 heroAttackAnimate->addSpriteFrame(frame1);
	 heroAttackAnimate->setDelayPerUnit(0.05);
	 heroAttackAnimate->setLoops(1);
	 auto ami = Animate::create(heroAttackAnimate);

	 return ami;
 }

 ActionInterval *AnimateClass::heroJumpAttack()
 {
	 Animation *jump_attack = Animation::create();
	 auto frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_jump0.png");
	 jump_attack->addSpriteFrame(frame1);
	 auto frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_jump_attick0.png");
	 jump_attack->addSpriteFrame(frame2);
	 auto frame3 = SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_jump_attick1.png");
	 jump_attack->addSpriteFrame(frame3);
	 jump_attack->setDelayPerUnit(0.4);
	 jump_attack->setLoops(1);
	 auto ami = Animate::create(jump_attack);
	 return ami;
 }

 ActionInterval *AnimateClass::heroHurt()
 {
	 Animation *hurt = Animation::create();
	 for (int i = 0; i < 2; i++)
	 {
		 std::string filename = StringUtils::format("hero_hurt%d.png", i);
		 auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		 hurt->addSpriteFrame(frame);
	 }
	 hurt->setDelayPerUnit(0.1);
	 hurt->setLoops(1);
	 auto ami = Animate::create(hurt);
	 return ami;
}

 ActionInterval *AnimateClass::heroDie(){
	 Animation *die = Animation::create();
	 for (int i = 0; i < 2; i++)
	 {
		 std::string filename = StringUtils::format("hero_die%d.png", i);
		 auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		 die->addSpriteFrame(frame);
	 }
	 die->setDelayPerUnit(0.5);
	 die->setLoops(1);
	 auto ami = Animate::create(die);
	 return ami;
 }

 ActionInterval *AnimateClass::heroSwordAnger()
 {
	 Animation *swordAnger = Animation::create();
	 for (int i = 7; i < 11; i++)
	 {
		 std::string filename = StringUtils::format("hero_attickSkill%d.png", i);
		 auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		 swordAnger->addSpriteFrame(frame);
	 }
	 swordAnger->setDelayPerUnit(WIN_TIME);
	 swordAnger->setLoops(WIN_NUMBER);
	 auto ami = Animate::create(swordAnger);
	 return ami;
 }

 ActionInterval * AnimateClass::heroLightningAnger()
 {
     Animation *lightning = Animation::create();
	 for (int i = 0; i < 2; i++)
	 {
		 std::string filename = StringUtils::format("hero_win%d.png", i);
		 auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		 lightning->addSpriteFrame(frame);
	 }
	 lightning->setDelayPerUnit(1);
	 lightning->setLoops(1);
	 auto ami = Animate::create(lightning);
	 return ami;
 }

 ActionInterval *AnimateClass::skillBig()
 {
     Animation *bigSkill = Animation::create();
	 for (int i = 0; i < 19; i++)
	 {
		 std::string filename = StringUtils::format("bigSkill%d.png", i);
		 auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		 bigSkill->addSpriteFrame(frame);
	 }
	 bigSkill->setDelayPerUnit(0.2);
	 bigSkill->setLoops(1);
	 auto ami = Animate::create(bigSkill);
	 return ami; 
 }

 ActionInterval * AnimateClass::heroStop()
 {
	  Animation *stop = Animation::create();
      auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_ release1.png");
	  stop->addSpriteFrame(frame);
	  stop->setDelayPerUnit(0.1);
	  stop->setLoops(1);
	  auto ami = Animate::create(stop);
	  return ami;
 }

 ActionInterval * AnimateClass::skillSwordAnger()
 {
     Animation *win = Animation::create();
	 for (int i = 0; i < 13; i++)
	 {
		 std::string filename = StringUtils::format("sword_skill%d.png", i);
		 auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		 win->addSpriteFrame(frame);
	 }
	 win->setDelayPerUnit(0.1);
	 win->setLoops(1);
	 auto ami = Animate::create(win);
	 return ami;
 }

 ActionInterval * AnimateClass::skillLightning()
 {
      Animation *lightning= Animation::create();
	 for (int i = 0; i < 8; i++)
	 {
		 std::string filename = StringUtils::format("kill_lightning%d.png", i);
		 auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		 lightning->addSpriteFrame(frame);
	 }
	 lightning->setDelayPerUnit(0.1);
	 lightning->setLoops(3);
	 auto ami = Animate::create(lightning);
	 return ami;
 }

 ActionInterval * AnimateClass::monsterRun(int id)
 {
     if(id == 1)
	 {
	     return goblinRun();
	 }
	 else if(id == 2)
	 {
	     return soldierRun();
	 }
	 else if(id == 3)
	 {
	     return boosRun();
	 }
	 return NULL;
 }

 ActionInterval * AnimateClass::monsterHurt(int id)
 {
      if(id == 1)
	 {
	     return goblinHurt();
	 }
	 else if(id == 2)
	 {
	     return soldierHurt();
	 }
	 else if(id == 3)
	 {
	     return boosHurt();
	 }
	 return NULL;
 }
 
 ActionInterval * AnimateClass::monsterAttack(int id)
 {
     if(id == 1)
	 {
	     return goblinAttack();
	 }
	 else if(id == 2)
	 {
	     return soldierAttick();
	 }
	 else if(id == 3)
	 {
	     return boosAttick();
	 }
	 return NULL;
 }

 ActionInterval * AnimateClass::goblinRun()
 {
      Animation *run= Animation::create();
	 for (int i = 0; i < 6; i++)
	 {
		 std::string filename = StringUtils::format("run%d.png", i);
		 auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		 run->addSpriteFrame(frame);
	 }
	 run->setDelayPerUnit(0.1);
	 run->setLoops(-1);
	 return Animate::create(run);
 }

 //哥布林受伤动画
 ActionInterval * AnimateClass::goblinHurt()
 {
     Animation *hurt= Animation::create();
	 for(int i = 0; i < 1; i++)
	 {
		 std::string filename = StringUtils::format("hurt%d.png", i);
		 auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		 hurt->addSpriteFrame(frame);
	 }
	 hurt->setDelayPerUnit(0.1);
	 hurt->setLoops(1);
	 return Animate::create(hurt);
 }

 ActionInterval * AnimateClass::goblinAttack()
 {
     Animation *attack= Animation::create();
	 for (int i = 0; i < 7; i++)
	 {
		 std::string filename = StringUtils::format("attack%d.png", i);
		 auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		 attack->addSpriteFrame(frame);
	 }
	 attack->setDelayPerUnit(0.1);
	 attack->setLoops(1);
	 return Animate::create(attack);
 }

 ActionInterval * AnimateClass::soldierRun()
 {
     Animation *run= Animation::create();
	 for (int i = 0; i < 7; i++)
	 {
		 std::string filename = StringUtils::format("sol_run%d.png", i);
		 auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		 run->addSpriteFrame(frame);
	 }
	 run->setDelayPerUnit(0.1);
	 run->setLoops(-1);
	 return Animate::create(run);
 }

 ActionInterval * AnimateClass::soldierHurt()
 {
      Animation *hurt= Animation::create();
	 for (int i = 0; i < 1; i++)
	 {
		 std::string filename = StringUtils::format("sol_hurt%d.png", i);
		 auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		 hurt->addSpriteFrame(frame);
	 }
	 hurt->setDelayPerUnit(0.1);
	 hurt->setLoops(1);
	 return Animate::create(hurt);
 }

 ActionInterval * AnimateClass::soldierAttick()
 {
     Animation *run= Animation::create();
	 for (int i = 0; i < 8; i++)
	 {
		 std::string filename = StringUtils::format("sol_attick%d.png", i);
		 auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		 run->addSpriteFrame(frame);
	 }
	 run->setDelayPerUnit(0.1);
	 run->setLoops(1);
	 return Animate::create(run);
 }

 ActionInterval * AnimateClass::boosRun()
 {
     Animation *run= Animation::create();
	 for (int i = 0; i < 7; i++)
	 {
		 std::string filename = StringUtils::format("boss_run%d.png", i);
		 auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		 run->addSpriteFrame(frame);
	 }
	 run->setDelayPerUnit(0.1);
	 run->setLoops(-1);
	 return Animate::create(run);
 }

 ActionInterval * AnimateClass::boosHurt()
 {
      Animation *hurt= Animation::create();
	  for(int i = 0; i < 1; i++)
	  {
		 std::string filename = StringUtils::format("boss_hurt%d.png", i);
		 auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		 hurt->addSpriteFrame(frame);
	  }
	 hurt->setDelayPerUnit(0.1);
	 hurt->setLoops(1);
	 return Animate::create(hurt);
 }

 ActionInterval * AnimateClass::boosAttick()
 {
     Animation *attack= Animation::create();
	 for (int i = 0; i < 13; i++)
	 {
		 std::string filename = StringUtils::format("boss_attick%d.png", i);
		 auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		 attack->addSpriteFrame(frame);
	 }
	 attack->setDelayPerUnit(0.1);
	 attack->setLoops(1);
	 return Animate::create(attack);
 }
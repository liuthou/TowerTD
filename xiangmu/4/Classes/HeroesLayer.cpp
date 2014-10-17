#include "HeroesLayer.h"
#include "Hero_SwordPlay.h"
#include "SkillBullet.h"
#include "BasePet.h"
#include "PetWolf.h"
#include "ScoreLayer.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

HeroesLayer * HeroesLayer::create(std::string fileName)
{
	HeroesLayer * heroesLayer = new HeroesLayer();
	if (heroesLayer && heroesLayer->init(fileName))
	{
		heroesLayer->autorelease();
		return heroesLayer;
	}
	CC_SAFE_DELETE(heroesLayer);
	return nullptr;
}



bool HeroesLayer::init(std::string fileName)
{
	if (!Layer::init())
	{
		return false;
	}
	touchTime = 0;
	may = false;
	xy_cut = ccpLength(Vec2(960, 640));
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hero/hero.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hero/Pet.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Bullet/Bullet.plist");
	this->setHeroFileName(fileName);

	return true;
}

void HeroesLayer::createHeroes(std::string fileName)
{
	if (fileName == "HeroFly1.png")
	{
		hero = Hero_SwordPlay::create();
		hero->setName("hero");
		this->addChild(hero);
		//hero->retain();
	}
}

void HeroesLayer::startTime(float t)
{
	touchTime++;
	if (touchTime == 2 && pet->getIsMay() == true)
	{
		pet->powerOver();
		may = true;
	}
}

void HeroesLayer::onEnter(){

	Layer::onEnter();

	createHeroes(this->getHeroFileName());
	Vec2 p(300, 300);
	pet = PetWolf::create(p);
	//pet->retain();
	pet->setName("pet");
	this->addChild(pet);

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = [=](std::vector<Touch *>vt, Event * e){
		for (auto it : vt)
		{
			if (vt.size() > 2)
			{
				return;
			}
			if (hero->getBoundingBox().containsPoint(it->getLocation()))
			{
				Vbegan_1 = it->getLocation();
			}
			else
			{
				hero->setIsAddFire(false);
				Vbegan_2 = it->getLocation();
				this->schedule(schedule_selector(HeroesLayer::startTime), 1);
			}
		}
	};
	listener->onTouchesMoved = [=](std::vector<Touch *>vt, Event * e){
		for (auto it : vt)
		{
			if (vt.size() > 2)
			{
				return;
			}
			if (hero->getBoundingBox().containsPoint(it->getPreviousLocation()))
			{
				//Vec2 p = it->getDelta();
				Point movePoint = it->getLocation();

				//Touch的左边界
				float pleft = movePoint.x - hero->getContentSize().width / 2;
				//如果超出Layer的碰撞框,重设置movePoint的x为主角宽度一半
				if (pleft < this->getBoundingBox().origin.x) {
					movePoint.x = hero->getContentSize().width / 2;
				}
				float pright = movePoint.x + hero->getContentSize().width / 2;
				if (pright>this->getBoundingBox().size.width) {
					movePoint.x = this->getBoundingBox().size.width - hero->getContentSize().width / 2;
				}
				float pup = movePoint.y + hero->getContentSize().height / 2;
				if (pup > this->getBoundingBox().size.height) {
					movePoint.y = this->getBoundingBox().size.height - hero->getContentSize().height / 2;
				}
				float pdown = movePoint.y - hero->getContentSize().height / 2;
				if (pdown < this->getBoundingBox().origin.y) {
					movePoint.y = hero->getContentSize().height / 2;

				}
				hero->setPosition(movePoint);
				return;
			}
			if (ccpDistance(it->getLocation(), Vbegan_2) < 30)
			{
				return;
			}
			float length = ccpLength(it->getLocation());
			if (length < xy_cut)
			{
				xy_cut = length;
				Vmin = it->getLocation();
			}
		}

	};
	listener->onTouchesEnded = [=](std::vector<Touch *>vt, Event * e){
		for (auto it : vt)
		{
			if (vt.size() > 2)
			{
				return;
			}
			if (!hero->getBoundingBox().containsPoint(it->getLocation()))
			{
				Vec2 thisTouch = it->getLocation();
				if (thisTouch.x > Vbegan_2.x - 10 && thisTouch.x < Vbegan_2.x + 10 && thisTouch.y > Vbegan_2.y - 10 && thisTouch.y < Vbegan_2.y + 10 && touchTime >= 2)
				{
					//释放蓄力
					if (may == true)
					{
						pet->setIsMove(false);

						pet->powerRelease();

						may = false;
						touchTime = 0;
						this->unschedule(schedule_selector(HeroesLayer::startTime));
						hero->setIsAddFire(true);
					}

				}
				else
				{

					touchTime = 0;
					this->unschedule(schedule_selector(HeroesLayer::startTime));
					hero->setIsAddFire(true);

					pet->stopPowerOver();


					Vend = it->getLocation();
					float y_sub = Vend.y - Vmin.y;
					if (Vmin == it->getPreviousLocation())
					{
						xy_cut = ccpLength(Vec2(960, 640));
						return;
					}
					float Trianglex = ccpDistance(Vbegan_2, Vmin);
					float Triangley = ccpDistance(Vmin, Vend);
					float Trianglexy = ccpDistance(Vend, Vbegan_2);
					float Angle_xy = (Trianglex * Trianglex + Triangley * Triangley - Trianglexy * Trianglexy) / 2 / Trianglex / Triangley;
					//log("xy + %f",Angle_xy);
					float Angle_triangle = CC_RADIANS_TO_DEGREES(acos(Angle_xy));
					//log("%f",Angle_triangle);
					GameScene * scene =(GameScene *) Director::getInstance()->getRunningScene();
					ScoreLayer * toolsNumber = (ScoreLayer *)scene->getScoreLayer();
				//	auto toolsNumber = ScoreLayer::create();
					if (ccpDistance(Vmin, Vend) > 30 && Angle_triangle > 60 && Angle_triangle < 120 && toolsNumber->getvectornumber() > 0)
					{
						//释放雷
						auto bigSkill = SkillBullet::create(hero->getPosition(), 100, "Bomb1.png", 1, 1);
						this->addChild(bigSkill);
						SimpleAudioEngine::getInstance()->playEffect("bombMusic.wma");
						touchTime = 0;
						this->unschedule(schedule_selector(HeroesLayer::startTime));
						hero->setIsAddFire(true);
						auto center = __NotificationCenter::getInstance();
						center->postNotification("ToolsDelete", this);
					}
				}
			}
			if (hero->getBoundingBox().containsPoint(it->getLocation()))
			{
				pet->stopPowerOver();

				touchTime = 0;
				this->unschedule(schedule_selector(HeroesLayer::startTime));
				hero->setIsAddFire(true);
			}

			touchTime = 0;
			this->unschedule(schedule_selector(HeroesLayer::startTime));
			hero->setIsAddFire(true);

			xy_cut = ccpLength(Vec2(960, 640));
			flag = 0;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void HeroesLayer::setHeroDie()
{
	hero = NULL;
}

void HeroesLayer::setTouchesStop(bool isStop)
{
	if (isStop) {
		Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
	}
	else{
		Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this);
	}

}
#include "T_ExorbitanceScene.h"
#include "ExorbitanceScene.h"
#include "DataGeares.h"
#include "HeroMacro.h"
#include "Skilles.h"
#include "DataCacheHero.h"
#include "StartScene.h"
#include "DataCacheGear.h"
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;

int fileCopy(const char *sreFileName,const char * path)
{
	Data data = FileUtils::getInstance()->getDataFromFile(sreFileName);
	FILE * fb = fopen(path, WB);
	fwrite(data.getBytes(), data.getSize(), 1, fb);
	fflush(fb);
	fclose(fb);
	return 1;
}

Scene * ExorbitanceScene::createScene()
{
    Scene * scene = Scene::create();
	Layer * layer = ExorbitanceScene::create();
	scene->addChild(layer);
	return scene;
}

bool ExorbitanceScene::init()
{
	if(!Layer::init()){
	   return false;
	}
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(HERO_PICTURE_PLIST);
    std::string df = FileUtils::getInstance()->getWritablePath() + SAVEYOURSISTERSQL;
	if(!FileUtils::getInstance()->isFileExist(df))
	{
	     log("There is a sqlite!");
	}
	else
	{
		std::string fe = FileUtils::getInstance()->fullPathForFilename(SAVEYOURSISTERSQL);
		std::string df = FileUtils::getInstance()->getWritablePath() + SAVEYOURSISTERSQL;
        log("database path == %s", df.c_str());
		fileCopy(fe.c_str(),df.c_str());
	}
	//数据库操作
	opendb();
	querySkillDb();
	queryHeroDb();
	queryGearDb();
	//开始界面显示
    Size vSize = Director::getInstance()->getVisibleSize();
	//背景
	Sprite * ground = Sprite::create("startground.png");
	ground->setPosition(vSize/2);
	this->addChild(ground);
	//进入游戏按钮实现
	Vec2 vOrigin = Director::getInstance()->getVisibleOrigin();
	ClippingNode * cl = ClippingNode::create();
	cl->setAlphaThreshold(0.5f);
	cl->setAnchorPoint(Vec2(0.5,0.5));
	this->addChild(cl);
	auto l1 = Label::createWithTTF("SAVE,YOUR,SISTER","Marker Felt.ttf",80,Size::ZERO,
		TextHAlignment::CENTER); 
	l1->setColor(Color3B::BLACK);
	l1->setPosition(400,500);
	cl->addChild(l1);
	auto sp = Sprite::create("Orb_Icons_003.png");
	sp->setPosition(l1->getPosition().x - l1->getContentSize().width/2,l1->getPositionY());
	cl->setStencil(sp);
	auto mv = MoveBy::create(fabsf(vSize.width/100),Vec2(vSize.width-l1->getPositionX(),0));
	sp->runAction(RepeatForever::create(Sequence::create(mv,mv->reverse(),NULL)));
	auto bg = Sprite::create("jnm.png");
	bg->setPosition(300,300);
	this->addChild(bg);
	auto lb = Label::createWithTTF("Please Click On The Screen","Marker Felt.ttf",30,Size::ZERO,
	TextHAlignment::CENTER);
	lb->setPosition(600,300);
	lb->setColor(Color3B::BLACK);
	lb->runAction(RepeatForever::create(Sequence::create(FadeIn::create(0.8),FadeOut::create(0.8),NULL)));
	this->addChild(lb);
	auto listen = EventListenerTouchOneByOne::create();
	listen->onTouchBegan = [=](Touch *t,Event *e){
		auto scene = StartScene::createScene();
	    Director::getInstance()->replaceScene(scene);
        SimpleAudioEngine::getInstance()->playEffect("select.wav");
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen,this);
	
	return true;
}
void ExorbitanceScene::onEnter()
{
	Layer::onEnter();

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("uiBackGround.mp3");//ui背景音乐
	SimpleAudioEngine::getInstance()->preloadEffect("ItemPress.wav");//ui选层按钮音乐
	SimpleAudioEngine::getInstance()->preloadEffect("select.wav");//ui选关音乐select equip.mp3
	SimpleAudioEngine::getInstance()->preloadEffect("select equip.mp3");

}

void ExorbitanceScene::opendb()
{
	std::string fileName = FileUtils::getInstance()->getWritablePath() + SAVEYOURSISTERSQL;
	_pdb = NULL;
	//判断数据库是否打开
	if(!(sqlite3_open(fileName.c_str(),&_pdb) == SQLITE_OK)){
	    return ;
	}
}

void ExorbitanceScene::queryHeroDb()
{
	sqlite3_stmt * stmt = nullptr;
	for(int i = 1;i <= 1;i++)
	{
		//判断数据库中猪脚表是否打开
	   if(!(sqlite3_prepare(_pdb,SELECT_HERO,-1,&stmt,nullptr) == SQLITE_OK))
	   {
		     return;
	   }
	   //绑定id
//	   sqlite3_bind_int(stmt, 1, i);
        sqlite3_bind_int(stmt, 1, i);
	   //遍历每一列的数据
       while (sqlite3_step(stmt) == SQLITE_ROW)
       {   
		    int id =  sqlite3_column_int(stmt, 0);
			const unsigned char * name = sqlite3_column_text(stmt,1);
			int hero_hp = sqlite3_column_int(stmt, 3);
			int hero_mp = sqlite3_column_int(stmt, 4);
			int hero_attack = sqlite3_column_int(stmt, 5);
			double hero_defense = sqlite3_column_double(stmt, 6);
			double hero_agility = sqlite3_column_double(stmt, 7);
			int hero_exp = sqlite3_column_int(stmt, 8);
			int hero_nowExp = sqlite3_column_int(stmt, 9);
			int hero_level = sqlite3_column_int(stmt, 10);
			int hero_needExp = sqlite3_column_int(stmt, 11);
			int hero_sp = sqlite3_column_int(stmt, 12);
			const unsigned char * hero_introduce = sqlite3_column_text(stmt,2);
			DataCacheHero * hero = DataCacheHero::getInstance();
			hero->setId(id);
			hero->setName((char *)name);
			hero->setHpValue(hero_hp);
			hero->setMpValue(hero_mp);
			hero->setAttackValue(hero_attack);
			hero->setDefenseValue(hero_defense);
			hero->setAgilityValue(hero_agility);
			hero->setExpValue(hero_exp);
			hero->setNowExpValue(hero_nowExp);
			hero->setLevelValue(hero_level);
			hero->setNeedExpValue(hero_needExp);
			hero->setSpValue(hero_sp);
			hero->setIntroduce((char *)hero_introduce);
     	}
	 }
}

void ExorbitanceScene::querySkillDb()
{
	sqlite3_stmt * stmt = nullptr;
	for(int i = 1;i <= 3;i++)
	{
		if(!(sqlite3_prepare(_pdb,SELECT_SKILL,-1,&stmt,nullptr) == SQLITE_OK))
		{
			 return;
		}
        sqlite3_bind_int(stmt, 1, i);
       while (sqlite3_step(stmt) == SQLITE_ROW)
       {   
		    int id =  sqlite3_column_int(stmt, 0);
			int attick = sqlite3_column_int(stmt, 1);
			int skill_show = sqlite3_column_int(stmt, 2);
			int skill_consume = sqlite3_column_int(stmt, 3);
			int skill_grade = sqlite3_column_int(stmt, 4);
			double skill_addition = sqlite3_column_double(stmt, 5);
			int skill_sp = sqlite3_column_int(stmt, 6);
			DataCacheSkill * data = DataCacheSkill::create();
			data->setId(id);
			data->setAttickValue(attick);
			data->setIsShow(skill_show);
			data->setConsumeMp(skill_consume);
			data->setSkillGrade(skill_grade);
			data->setSkillAddition(skill_addition);
			data->setSkillUserSp(skill_sp);
			Skilles * _skilles = Skilles::getInstance();
			_skilles->addSkillRef(data);
     	}
	 }
}

void ExorbitanceScene::queryGearDb()
{
	sqlite3_stmt * stmt = nullptr;
	for(int i = 1;i <= 30;i++)
	{
		if(!(sqlite3_prepare(_pdb,SELECT_GEAR,-1,&stmt,nullptr) == SQLITE_OK))
		{
			 return; 
		}
	   sqlite3_bind_int(stmt, 1, i);
       while (sqlite3_step(stmt) == SQLITE_ROW)
       {   
		    int id =  sqlite3_column_int(stmt, 0);
			const unsigned char * name = sqlite3_column_text(stmt, 1);
			const unsigned char * pictureName = sqlite3_column_text(stmt, 2);
			int addAttick = sqlite3_column_int(stmt, 3);
			double addDefense = sqlite3_column_double(stmt, 4);
			double addAgility = sqlite3_column_double(stmt, 5);
			int gearType = sqlite3_column_int(stmt, 6);
			int gearQuality = sqlite3_column_int(stmt, 7);
			int heroHave = sqlite3_column_int(stmt, 8);
			int heroAdorn = sqlite3_column_int(stmt, 9);
			int haveNumber = sqlite3_column_int(stmt, 10);
			double gear_addition = sqlite3_column_double(stmt, 11);
			int gear_sp = sqlite3_column_int(stmt, 12);
			DataCacheGear * data = DataCacheGear::create();
			data->setId(id);
			data->setName((char *)name);
			data->setPictureName((char *)pictureName);
			data->setAttickValue(addAttick);
			data->setDefenseValue(addDefense);
			data->setAglityValue(addAgility);
			data->setGearType(gearType);
			data->setQuality(gearQuality);
			data->setHeroHave(heroHave);
			data->setHeroAdorn(heroAdorn);
			data->setHaveNumber(haveNumber);
			data->setAdditionValue(gear_addition);
			data->setGearUserSp(gear_sp);
			DataGeares * gear = DataGeares::getInstance();
			gear->addGearRef(data);
     	}
	 }
}

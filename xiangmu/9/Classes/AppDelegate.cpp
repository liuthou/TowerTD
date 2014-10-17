#include "AppDelegate.h"
#include "time.h"
#include "EnterLayer.h"
#include "DataCacheHero.h"
#include "Skilles.h"
#include "DataGeares.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
	srand(time(0));
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = EnterLayer::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	openDb();
}

void AppDelegate::openDb()
{
    std::string fileName = FileUtils::getInstance()->getWritablePath() + "SaveYourSisterSql.sqlite3";
	_pdb = NULL;
	//判断数据库是否打开
	if(!(sqlite3_open(fileName.c_str(),&_pdb) == SQLITE_OK)){
	    return ;
	}
    updataHero();
    updateSkill();
    updateGear();
}

void AppDelegate::updataHero()
{
    DataCacheHero * dataCacheHero = DataCacheHero::getInstance();
    const char * sql = "update ahero set hero_hp = ? , hero_mp = ? , hero_attick = ? , hero_defense = ? , hero_agility = ? , hero_exp = ? , hero_nowExp = ? , hero_level = ? , hero_needExp = ? , hero_sp = ?  where  id = 1";
    sqlite3_stmt * stmt = nullptr;
    if(!(sqlite3_prepare(_pdb,sql,-1,&stmt,nullptr) == SQLITE_OK))
    {
            return;
    }
    log("%d, %d",dataCacheHero->getLevelValue(), dataCacheHero->getMpValue());
    sqlite3_bind_int(stmt, 1, dataCacheHero->getHpValue());
    sqlite3_bind_int(stmt, 2, dataCacheHero->getMpValue());
    sqlite3_bind_int(stmt, 3, dataCacheHero->getAttackValue());
    sqlite3_bind_double(stmt, 4, dataCacheHero->getDefenseValue());
    sqlite3_bind_double(stmt, 5, dataCacheHero->getAgilityValue());
    sqlite3_bind_int(stmt, 6, dataCacheHero->getExpValue());
    sqlite3_bind_int(stmt, 7, dataCacheHero->getNowExpValue());
    sqlite3_bind_int(stmt, 8, dataCacheHero->getLevelValue());
    sqlite3_bind_int(stmt, 9, dataCacheHero->getNeedExpValue());
    sqlite3_bind_int(stmt, 10, dataCacheHero->getSpValue());
	sqlite3_step(stmt);
}

void AppDelegate::updateGear()
{
    DataGeares * dataGeares = DataGeares::getInstance();
    sqlite3_stmt * stmt = nullptr;
    int i = 1;
    for (auto x = dataGeares->getDataGeares().begin(); x != dataGeares->getDataGeares().end(); x++ , i++) {
        const char * sql = "update gear set addAttick = ? , addDefense = ? , addAgility = ? , quality = ? , hero_adorn = ? , gear_addition = ? , gear_sp = ? where  id = ?";
        if(!(sqlite3_prepare(_pdb,sql,-1,&stmt,nullptr) == SQLITE_OK))
        {
            return;
        }
        sqlite3_bind_int(stmt, 1, (*x)->getAttickValue());
        sqlite3_bind_double(stmt, 2, (*x)->getDefenseValue());
        sqlite3_bind_double(stmt, 3, (*x)->getAglityValue());
        sqlite3_bind_int(stmt, 4, (*x)->getQuality());
        sqlite3_bind_int(stmt, 5, (*x)->getHeroAdorn());
        sqlite3_bind_double(stmt, 6, (*x)->getAdditionValue());
        sqlite3_bind_int(stmt, 7, (*x)->getGearUserSp());
        sqlite3_bind_int(stmt, 8, (*x)->getId());
        sqlite3_step(stmt);
    }
}

void AppDelegate::updateSkill()
{
    Skilles *skilles = Skilles::getInstance();
    sqlite3_stmt * stmt = nullptr;
    int i = 1;
    for (auto x = skilles->getSkilles().begin(); x != skilles->getSkilles().end(); x++ , i++) {
        const char * sql = "update bskill set skill_attick = ? , skill_mp = ? , skill_grade = ? , skill_addition = ? , skill_sp = ?  where  id = ?";
        if(!(sqlite3_prepare(_pdb,sql,-1,&stmt,nullptr) == SQLITE_OK))
        {
            return;
        }
        sqlite3_bind_int(stmt, 1, (*x)->getAttickValue());
        sqlite3_bind_int(stmt, 2, (*x)->getConsumeMp());
        sqlite3_bind_int(stmt, 3, (*x)->getSkillGrade());
        sqlite3_bind_double(stmt, 4, (*x)->getSkillAddition());
        sqlite3_bind_int(stmt, 5, (*x)->getSkillUserSp());
        sqlite3_bind_int(stmt, 6, (*x)->getId());
        sqlite3_step(stmt);
    }
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

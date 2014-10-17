//
//  UserDateSolve.cpp
//  herojump
//
//  Created by lanou3g on 14-10-3.
//
//

#include "UserDateSolve.h"
#include <stdlib.h>
int UserDateSolve::thisTimeScore = 0;
sqlite3* UserDateSolve::pdb = NULL;
int fileCopy(const char *srcFilename,const char *desFileName){
    if(FileUtils::getInstance()->isFileExist(desFileName)){
        return 1;
    }
    Data data = FileUtils::getInstance()->getDataFromFile(srcFilename);
    FILE *fp = fopen(desFileName, "wb");
    fwrite(data.getBytes(), data.getSize(), 1, fp);
    fflush(fp);
    fclose(fp);
    
    return 1;
}

void UserDateSolve::userDateSolve(int score){
    thisTimeScore = score;
    std::string sfileName = FileUtils::getInstance()->fullPathForFilename("HeroJump.sqlite");
    std::string dfileName = FileUtils::getInstance()->getWritablePath()+"HeroJump.sqlite";
    fileCopy(sfileName.c_str(), dfileName.c_str());
    opendb();
    /** insertdb();
     *  进行一下查询 如果分数大于当前数据库中的分数，就直接插入到数据库
     */
    querybd();

}

int UserDateSolve::selectMaxScore(){
   
    int maxScore;
    std::string sfileName = FileUtils::getInstance()->fullPathForFilename("HeroJump.sqlite");
    std::string dfileName = FileUtils::getInstance()->getWritablePath()+"HeroJump.sqlite";
    
    fileCopy(sfileName.c_str(), dfileName.c_str());
    opendb();
    
    sqlite3_stmt *stmt = nullptr;
    if(sqlite3_prepare(pdb, "select * from UserDate where userName = ? ", -1, &stmt, nullptr) !=SQLITE_OK){
        return 0;
    }
    sqlite3_bind_text(stmt, 1, "zhangsan", -1, nullptr);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        maxScore= sqlite3_column_int(stmt, 1);
    }
    sqlite3_close(pdb);
    return maxScore;

}

void UserDateSolve::opendb(){

    std::string  fileName = FileUtils::getInstance()->getWritablePath() + "HeroJump.sqlite";
    //pdb声明成为成员变量
    pdb = nullptr;
    if(sqlite3_open(fileName.c_str(), &pdb) != SQLITE_OK){//pdb就是帮忙指向一个地方。
        return ;
    }
}

int UserDateSolve::querybd(){
    sqlite3_stmt *stmt = nullptr;
    int score;
    if(sqlite3_prepare(pdb, "select * from UserDate where userName = ? ", -1, &stmt, nullptr) !=SQLITE_OK){
        return 0;
    }
    //在查询的时候绑定的第二个参数就是第几个问号的位置。最后一个参数是这个位置的值是什么。
    sqlite3_bind_text(stmt, 1, "zhangsan", -1, nullptr);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        score= sqlite3_column_int(stmt, 1);
        //如果本次的分数小于上一次的分数就对数据库进行更行0
        if (score < thisTimeScore ) {
            updatedb();
        }
    }
    return score;
    
}

void UserDateSolve::insertdb(){
    const char * sql = "insert into UserDate (userName, thisTimeScore, money) values(?, ?, ?)";
    sqlite3_stmt *stmt = nullptr;
    sqlite3_prepare(
                    pdb,        /* Database handle */
                    sql,       /* SQL statement, UTF-8 encoded */
                    -1,        /* Maximum length of zSql in bytes. */
                    &stmt,     /* OUT: Statement handle */
                    nullptr    /* OUT: Pointer to unused portion of zSql */
                    );
    //sqlite3_bind_text(stmt,1,"smll",-1,nullptr);
    sqlite3_bind_text(stmt, 1, "zhangsan",  -1, nullptr);
    sqlite3_bind_int(stmt, 2, 100);
    sqlite3_bind_int(stmt, 3, 200);
    sqlite3_step(stmt);
    
    sqlite3_commit_hook(pdb, nullptr, nullptr);
}


void UserDateSolve::deletedb(){
    const char *sql = "update Enemy set score =100 and money = 100 where name = 'zhansan' ";
    sqlite3_exec(pdb, sql, nullptr, nullptr, nullptr);
}


void UserDateSolve::updatedb(){   
    const char *sql = StringUtils::format("update userDate set score = %d where userName = 'zhangsan' ",thisTimeScore).c_str();
    sqlite3_exec(pdb, sql, nullptr, nullptr, nullptr);
}

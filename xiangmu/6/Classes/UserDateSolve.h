//
//  UserDateSolve.h
//  herojump
//
//  Created by lanou3g on 14-10-3.
//
//

#ifndef __herojump__UserDateSolve__
#define __herojump__UserDateSolve__

#include "cocos2d.h"
#include "sqlite3.h"
#include <iostream>
using namespace cocos2d;

int fileCopy(const char *srcFilename,const char *path);
class UserDateSolve{
private:
    static int thisTimeScore;
    static sqlite3* pdb;
    
public:

    static void userDateSolve(int score);
    static void opendb();
    static int querybd();
    static void insertdb();
    static void deletedb();
    static void updatedb();
    static int selectMaxScore();
};




#endif /* defined(__herojump__UserDateSolve__) */

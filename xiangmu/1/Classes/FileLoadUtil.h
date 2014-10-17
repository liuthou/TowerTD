//
//  FileLoadUtil.h
//  Chapter9_6_LoadCsv
//
//  Created by 闫鑫 on 14-6-14.
//
//

#ifndef __Chapter9_6_LoadCsv__FileLoadUtil__
#define __Chapter9_6_LoadCsv__FileLoadUtil__

#include "cocos2d.h"
#include "StringUtil.h"

class FileLoadUtil
{
public:
    
    StrVec getDataLines(const std::string &rSCsvFilePath)
    {
        StrVec linesList;
        
        if (!cocos2d::FileUtils::getInstance()->isFileExist(rSCsvFilePath))
            return linesList;
        
        ssize_t pSize = 0;
        
        StringUtil tStringUtil;
        
        unsigned char *chDatas = cocos2d::FileUtils::getInstance()->getFileData(rSCsvFilePath, "r", &pSize);
        
        if(chDatas) linesList = tStringUtil.split((char *)chDatas, "\n");
        
        return linesList;
    }
};

#endif /* defined(__Chapter9_6_LoadCsv__FileLoadUtil__) */

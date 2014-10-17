//
//  LocalDataUtil.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-10-8.
//
//

#include "LocalDataUtil.h"

LocalDataUtil *LocalDataUtil::_gInstance;

bool LocalDataUtil::init()
{
    bool bRet = false;
    do
    {
        auto pFileUtil = FileUtils::getInstance();
        _sLevelDataFileName = pFileUtil->getWritablePath() + DATAFILE;
        _levelData = pFileUtil->getValueMapFromFile(_sLevelDataFileName);
        
        registerLevelDataChangeEvent();
        bRet = true;
    }
    while (0);
    
    return  bRet;
}

LocalDataUtil::~LocalDataUtil()
{
    NOTIFY->removeAllObservers(this);
}

ValueMap &LocalDataUtil::getLevelData()
{
    return _levelData;
}

void LocalDataUtil::setLevelData(const ValueMap &rValueMap)
{
    _levelData = rValueMap;
    FileUtils::getInstance()->writeToFile(_levelData, _sLevelDataFileName);
}

void LocalDataUtil::registerLevelDataChangeEvent()
{
    NOTIFY->addObserver(this, callfuncO_selector(LocalDataUtil::levelDataChange), LEVELDATACHANGE, nullptr);
}

void LocalDataUtil::levelDataChange(Ref *pData)
{
    auto tLevelData = *(reinterpret_cast<std::tuple<int, int, int, int>*>(pData));
    auto tLevelType = std::get<0>(tLevelData);
    auto tData = std::get<1>(tLevelData);
    auto tThemeIndex = std::get<2>(tLevelData);
    auto tLevelIndex = std::get<3>(tLevelData);
    auto tLevelKey = StringUtils::format(LEVELKEY, tThemeIndex, tLevelIndex);
    auto tCurLevelData = _levelData[tLevelKey].asInt();
    auto tCarrotType = tCurLevelData / 10;
    auto tBarrierCleanFlag = tCurLevelData % 10;
    
    if(!tLevelType)
    {
        if(tCarrotType < tData) _levelData[tLevelKey] = StringUtils::format("%d%d", tData, tBarrierCleanFlag);
    }
    else
    {
        _levelData[tLevelKey] = StringUtils::format("%d%d", tCarrotType, tData);
    }
    
    FileUtils::getInstance()->writeToFile(_levelData, _sLevelDataFileName);
}









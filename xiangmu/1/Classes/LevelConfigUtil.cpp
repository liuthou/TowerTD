//
//  LevelConfigUtil.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-9-26.
//
//

#include "LevelConfigUtil.h"
#include "../cocos2d/external/tinyxml2/tinyxml2.h"
#include "CsvUtil.h"
#include "SceneManager.h"
using namespace tinyxml2;

LevelConfigUtil *LevelConfigUtil::_gInstance;

LevelConfigUtil::LevelConfigUtil()
{
}

LevelConfigUtil::~LevelConfigUtil()
{
    CC_SAFE_DELETE(_pEffectTowers);
}


bool LevelConfigUtil::init()
{
    bool bRet = false;
    
    do
    {
        _pEffectTowers = new std::vector<std::string>;
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void LevelConfigUtil::loadLevelConfig()
{
    _pEffectTowers->clear();
    
	tinyxml2::XMLDocument tXmlDoc;
    
    auto sFileName = FileUtils::getInstance()->fullPathForFilename(LEVELCONFIGFILENAME);
    
    auto tIndex = sFileName.find(LEVELCONFIGFILENAME);
    
    sFileName = sFileName.substr(0, tIndex);
    
    auto tfile = LEVELCONFIGFILENAME.substr(2, LEVELCONFIGFILENAME.size() - 2);
    
    sFileName = sFileName + tfile;
    
    tXmlDoc.LoadFile(sFileName.c_str());
    
    auto pRoot = tXmlDoc.RootElement();
    
    auto pSceneManager = SceneManager::getInstance();
    
    auto pLevelElement = pRoot->FirstChildElement(StringUtils::format("%d_%02d", pSceneManager->getCurPageIndex() + 1, pSceneManager->getCurLevelIndex() + 1).c_str());
    
    auto pElement = pLevelElement->FirstChildElement();
    
    while (pElement)
    {
        if(LEVELCONFIGTYPE[0] == pElement->Name())
            _iCurPageIndex = pElement->IntAttribute(LEVELCONFIGTYPE[0].c_str());
        if(LEVELCONFIGTYPE[1] == pElement->Name())
            _iCurLevelIndex = pElement->IntAttribute(LEVELCONFIGTYPE[1].c_str());
        if(LEVELCONFIGTYPE[2] == pElement->Name())
            _iCurLevelMoney = pElement->IntAttribute(LEVELCONFIGTYPE[2].c_str());
        if(LEVELCONFIGTYPE[3] == pElement->Name())
            _iMonsterBatchCount = pElement->IntAttribute(LEVELCONFIGTYPE[3].c_str());
    
        
        if(TOWERTYPE == pElement->Name())
        {
            auto pTower = pElement->FirstChildElement();

            while (pTower)
            {
                _pEffectTowers->push_back(pTower->Name());
                pTower = pTower->NextSiblingElement();
            }
            return;
        }
        pElement = pElement->NextSiblingElement();
    }
}

std::tuple<int, int, int, std::vector<std::string>> LevelConfigUtil::getLevelConfig()const
{
    return std::make_tuple(_iCurPageIndex, _iCurLevelIndex, _iMonsterBatchCount, *_pEffectTowers);
}

std::vector<std::string> LevelConfigUtil::getCurLevelTowersInfo()const
{
    return *_pEffectTowers;
}

int LevelConfigUtil::getCurLevelMonsterBatchCount()const
{
    return _iMonsterBatchCount;
}

int LevelConfigUtil::getCurLevelMoney()const
{
    return _iCurLevelMoney;
}

void LevelConfigUtil::buildLevelConfig()
{
    auto pCsvUtil = CsvUtil::getInstance();
    pCsvUtil->addFileData(LEVELCSVFILE);
    
    auto tColumnRowCount = pCsvUtil->getFileRowColNum(LEVELCSVFILE);
    
    auto tColumn = std::get<0>(tColumnRowCount);
    auto tRow = std::get<1>(tColumnRowCount);
    
	auto pXmldoc = new tinyxml2::XMLDocument;
    
    auto pLevelConfigRoot = pXmldoc->NewElement(LEVELCONFIGROOT.c_str());
    pXmldoc->LinkEndChild(pLevelConfigRoot);
    
    for (int row = 1; row < tRow; ++row)
    {

        auto tColumnCount = 0;
        auto tThemeIndex = pCsvUtil->getInt(row, 0, LEVELCSVFILE);
        auto tLevelIndex = pCsvUtil->getInt(row, 1, LEVELCSVFILE);
        
        auto pLevelElement = pXmldoc->NewElement(StringUtils::format("%d_%02d", tThemeIndex, tLevelIndex).c_str());
        pLevelConfigRoot->LinkEndChild(pLevelElement);
        for(int column = 0; column < 4; ++column)
        {
            auto pElement = pXmldoc->NewElement(LEVELCONFIGTYPE[column].c_str());
            auto tValue = pCsvUtil->getInt(row, column, LEVELCSVFILE);
            pElement->SetAttribute(LEVELCONFIGTYPE[column].c_str(), StringUtils::format("%d", tValue).c_str());
            pLevelElement->LinkEndChild(pElement);
            tColumnCount = column;
        }
        ++tColumnCount;
        auto pTowerElement = pXmldoc->NewElement(TOWERTYPE.c_str());
        pLevelElement->LinkEndChild(pTowerElement);
        for(; tColumnCount < tColumn; ++tColumnCount)
        {

            auto tValue = pCsvUtil->getInt(row, tColumnCount, LEVELCSVFILE);
            if(1 == tValue)
            {
                auto pElement = pXmldoc->NewElement(LEVELCONFIGTYPE[tColumnCount].c_str());
                pTowerElement->LinkEndChild(pElement);
            }
        }
    }
    
    pXmldoc->SaveFile((FileUtils::getInstance()->getWritablePath() + "LevelConfig.xml").c_str());
    pCsvUtil->releaseFile(LEVELCSVFILE);
    delete pXmldoc;
}




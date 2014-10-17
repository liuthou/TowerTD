//
//  CsvUtil.h
//  Chapter14_2_CardDefence01
//
//  Created by 闫鑫 on 14-7-11.
//
//

#ifndef __Chapter14_2_CardDefence01__CsvUtil__
#define __Chapter14_2_CardDefence01__CsvUtil__

#include <vector>
#include <map>
#include <string>

typedef std::vector<std::string> StrVec;

typedef std::vector< StrVec > StrDict;

typedef std::map< std::string, StrDict> CsvMap;

class CsvUtil
{
public:
    
    static CsvUtil* getInstance();
    
    static void destroyInstance();
    
    /**
     *  add csv file to dict
     *
     *  @param sPath is csv file path
     */
    virtual void addFileData(const std::string &rSPath);
    
    /**
     *  del csv file to dict
     *
     *  @param sPath is csv file path
     */
    virtual void releaseFile(const std::string &rSPath);
    

    /**
     *  get some row and some column value from some csv file
     *
     *  @param rRow        is row num
     *  @param rCol        is column num
     *  @param csvFilePath is some csv file
     *
     *  @return some row and some column real TextValue IntValue, DoubleValue,if this pos not be exsit return ""
     */
    virtual std::string getText(const int &rRow, const int &rCol, const std::string &rSCsvFilePath);
    virtual int getInt(const int &rRow, const int &rCol, const std::string &rSCsvFilePath);
    virtual double getDouble(const int &rRow, const int &rCol, const std::string &rSCsvFilePath);
    
    
    /**
     *  get some file row data
     *
     *  @param iRow          is row num
     *  @param rSCsvFilePath is some csv file
     *
     *  @return some row data
     */
    virtual StrVec getRowData(const int &rIRow, const std::string &rSCsvFilePath);
    
    /**
     *  get csv file row and column save tuple<int, int>
     *
     *  @param rSCsvFilePath csv file path
     *
     *  @return csv file row, column in tuple<int, int>
     */
    virtual std::tuple<int, int> getFileRowColNum(const std::string &rSCsvFilePath);
    
    /**
     *  find dest value in csv file row num
     *
     *  @param rSValue       find value
     *  @param rIValueCol    value column
     *  @param rSCsvFilePath csv file path
     *
     *  @return value in csv row
     */
    virtual int findValueInWithLine(const std::string &rSValue, const int &rIValueCol, const std::string &rSCsvFilePath);

protected:
    /**
     *  get csv file string vec
     *
     *  @param rSCsvFilePath csv file path
     *
     *  @return csv file strVec
     */
    virtual StrDict &getFileDict(const std::string &rSCsvFilePath);
    
    virtual ~CsvUtil();
    
private:
    
    CsvUtil();
    
    CsvUtil(const CsvUtil &rCsvUtil) = delete;
    
    CsvUtil &operator=(const CsvUtil &rCsvUtil) = delete;
    
private:
    
    static CsvUtil* _gInstance;
    
    /**
     * 
     */
    CsvMap* _pCsvMap;
};

#endif /* defined(__Chapter14_2_CardDefence01__CsvUtil__) */

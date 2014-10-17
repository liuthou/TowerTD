//
//  StringUtil.h
//  Chapter9_6_LoadCsv
//
//  Created by 闫鑫 on 14-6-14.
//
//

#ifndef __Chapter9_6_LoadCsv__StringUtil__
#define __Chapter9_6_LoadCsv__StringUtil__

class StringUtil
{
public:
    
    StrVec split(const std::string &rSSrcStr, const std::string &rSSep)
    {
        StrVec stringList;
        
        int size = rSSrcStr.size();
        
        std::string str(rSSrcStr);
        
        int startIndex = 0;
        
        int endIndex = 0;
        
        endIndex = str.find(rSSep);
        
        std::string splitStr = "";
        
        while (endIndex > 0)
        {
            splitStr = str.substr(startIndex, endIndex);
            
            stringList.push_back(splitStr);
            
            str = std::string(str.substr(endIndex + 1, size));
            
            endIndex = str.find(rSSep);
        }
        
        if (str.compare("") != 0) {
            stringList.push_back(str);
        }
        return stringList;
    }
};


#endif /* defined(__Chapter9_6_LoadCsv__StringUtil__) */

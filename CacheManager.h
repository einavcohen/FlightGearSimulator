//
// Created by einav on 09/01/19.
//

#ifndef MILESTONE_2_CACHEMANAGER_H
#define MILESTONE_2_CACHEMANAGER_H

#include <string>

using namespace std;

class CacheManager{

public:

    virtual bool keyExistInCache (string key) = 0;

    virtual string loadFromCache(string key) = 0;

    virtual void saveDataInCache (string key, string solution) = 0;

};

#endif //MILESTONE_2_CACHEMANAGER_H

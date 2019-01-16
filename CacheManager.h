//
// Created by newbuntu on 14/01/19.
//

#ifndef UNTITLED1_CACHEMANAGERTEMP_H
#define UNTITLED1_CACHEMANAGERTEMP_H
using namespace std;

template <class P, class S>
class CacheManager {

public:

    CacheManager();

    virtual bool keyExistInCache (P key) = 0;

    virtual S loadFromCache(P key) = 0;

    virtual void saveDataInCache (P key, S solution) = 0;

};

template<class P, class S>
CacheManager<P, S>::CacheManager() {}

#endif //UNTITLED1_CACHEMANAGERTEMP_H

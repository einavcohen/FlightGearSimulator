#include <iostream>
#include "FileCacheManager.h"
#include "CacheManager.h"


int main() {
    string newpro="popo";
    string newsol="koko";

    FileCacheManager *fileCacheManager = new FileCacheManager();
    //fileCacheManager->loadFromCache("einav");
    fileCacheManager->keyExistInCache("popo");
    //fileCacheManager->saveDataInCache("gilad","koren");

    return 0;
}
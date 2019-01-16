//
// Created by einav on 10/01/19.
//

#ifndef MILESTONE_2_FILECACHEMANAGER_H
#define MILESTONE_2_FILECACHEMANAGER_H

#define DELIMITER '$'
#define CACHE_FILE "cachefile.txt"
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include "Solver.h"
#include "ClientHandler.h"
#include "CacheManager.h"
#include <mutex>

using namespace std;

class FileCacheManager : public CacheManager<string,string> {
    map<string, string> problemsToSolutions;
    mutex mtx;

    const vector<string> splitByDelimeter(std::string &input, const char &c);

    string readAllFileContent();

    void appendToFile(string fileName, string dataToAppend);

public:

    FileCacheManager();

    bool keyExistInCache(string key)override;

    string loadFromCache(std::string key)override;

    void saveDataInCache(string problem,string solution)override;

};
#endif //MILESTONE_2_FILECACHEMANAGER_H

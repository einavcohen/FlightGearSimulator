//
// Created by einav on 10/01/19.
//

#include "FileCacheManager.h"

bool FileCacheManager:: keyExistInCache(string key){
    try {
        loadFromCache(key);
        return true;
    }catch (...) { // no file exist or key doesnt exists in cache
        return false;
    }
}

//format of input file-
//problem$solution$problem$solution
FileCacheManager::FileCacheManager() {
    fstream inputFile(CACHE_FILE);
    if (!inputFile.is_open()) {
        throw std::runtime_error("could not open the file");
    }
}

string FileCacheManager:: readAllFileContent(){
        ifstream inputFile(CACHE_FILE);
        string fileContent((istreambuf_iterator<char>(inputFile)),
                        istreambuf_iterator<char>());

        return fileContent;
}

const vector<string> FileCacheManager:: splitByDelimeter(std::string &input, const char &c){

    string strbuff{""};
    vector<std::string> strvec;
    //remove EOL
    //input = input.substr(0,input.length()-2);

    for (auto n : input)
    {
        if (n != c)
            strbuff += n;
        else if (n == c && strbuff != "")
        {
            strvec.push_back(strbuff);
            strbuff = "";
        }
    }
    if (strbuff != "")
        strvec.push_back(strbuff);

    return strvec;

}

string FileCacheManager::loadFromCache(std::string key) {

    mtx.lock();

    string fileContent = readAllFileContent();

    vector<string> splitedvec = splitByDelimeter(fileContent, DELIMITER);

    std::map<std::string, std::string> cacheMap;

    for(auto it = splitedvec.begin();it != splitedvec.end(); it += 2 ) {
        std::string currKey = *it;
        std::string currValue = *(it + 1);
        cacheMap.insert(std::pair<std::string, std::string>(currKey, currValue));

    }

    auto valueIterator = problemsToSolutions.find(key);

    mtx.unlock();

    //iterator will be the end if key doesnt exists
    if(valueIterator != problemsToSolutions.end()){
        return valueIterator->second;
    } else {
        throw "key does not exist in cache. please check for existence first";
    }

}

void FileCacheManager:: appendToFile(string fileName, string dataToAppend) {

    fstream stream;
    stream.open(fileName, ios::app | ios::ate);

    stream << dataToAppend;

    stream.flush();
    stream.close();
}

void FileCacheManager::saveDataInCache(string problem,string solution) {

    mtx.lock();

    string data = problem + DELIMITER + solution + DELIMITER;

    appendToFile(CACHE_FILE, data);

    mtx.unlock();

}


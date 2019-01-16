//
// Created by newbuntu on 14/01/19.
//
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <cstdlib>
#include <thread>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <streambuf>
#include <iostream>
#include <iterator>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>
#include "StructSearchResult.h"
#include "SearchableMatrix.h"
#include "CacheManager.h"
#include "MyClientHandler.h"


CacheManager<string, string> *MyClientHandler::getCm() const {
    return cm;
}

Solver<Searchable *, SearchResult> *MyClientHandler::getSolver() const {
    return solver;
}

/**
 * Takes the string we got as parameter, split into multiple ints, (according to the delimiter
 * of char type we received as a second argument.)
 * insert them into a vector<int> and return it.
 * @param s
 * @param delimiter
 * @return tokens the vector containing all the ints
 */
std::vector<int> splitToInt(const std::string& s, char delimiter)
{
    std::vector<int> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(atoi(token.c_str()));
    }
    return tokens;
}

/**
 * Takes the string we got as parameter, split into multiple strings, (according to the delimiter
 * of char type we received as a second argument.)
 * insert them into a vector<int> and return it.
 * @param s
 * @param delimiter
 * @return tokens the vector containing all the ints
 */
std::vector<string> splitToStr(const std::string& s, char delimiter)
{
    std::vector<string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

/**
 * Counts the number of occurence of a certain char in a string and return the result
 * @param s
 * @param delimiter
 * @return number of occurence
 */
int count_occ(string s, char delimiter) {
    return std::count(s.begin(), s.end(), delimiter);
}
/**
 * Gets a vector of certain type, and return a string containing all the values from the vector
 * one after others separated with commas.
 * @tparam T
 * @param vec
 * @return oss.str() is the string containing all those values.
 */
template <class T>
string vecToString(vector<T> vec){
    std::ostringstream oss;

    if (!vec.empty())
    {
        // Convert all but the last element to avoid a trailing ","
        std::copy(vec.begin(), vec.end()-1,
                  std::ostream_iterator<T>(oss, ","));

        // Now add the last element with no delimiter
        oss << vec.back();
    }
    return oss.str();
}
/**
 * Appends 2 vectors then split the results in 2 others at the index 'size'. Returns the 2nd part and modify the original vector we got as 1st arg to contain the 1st part.
 * In case the 2nd vector is empty the function only splits the 1st vector.
 * @tparam T
 * @param s
 * @param str
 * @param size
 * @return split_hi which is the second part of the splitted vector.
 */
template <class T>
vector<T> splitVec(vector<T> &s, vector<T> str, int size) {
    if(!str.empty()) {
        s = MyClientHandler::append<T>(s, str);
        std::vector<T> split_lo(s.begin(), s.begin() + size);
        std::vector<T> split_hi(s.begin() + size, s.end());
        s = split_lo;
        return split_hi;
    }
    std::vector<T> split_lo(s.begin(), s.begin() + size);
    std::vector<T> split_hi(s.begin() + size, s.end());
    s = split_lo;
    return split_hi;
}
/**
 * Takes 2 vectors of same types and append them
 * @tparam T
 * @param a
 * @param b
 * @return a the new appended vector.
 */
template <class T>
vector<T> MyClientHandler::append(vector<T> a, vector<T> b){
    a.insert(std::end(a), std::begin(b), std::end(b));
    return a;
}

/**
 * Goes throught all the lines from the vector<string> it gots as argument, split it into multiple ints which were delimited by commas into each lines.
 * Checks if the number of ints we got after splitting the lines is matching the int matrix_size we got as 2nd arguments.
 * In the end the function returns a matrix of ints (construct with a vector of vector of int type) containing every int of the vector<string> lines
 * in which each rows have the same size (matrix_size) then return the matrix.
 * @param lines
 * @param matrix_size
 * @return vector<vector<int>> ret
 */
vector<vector<int>> processLines(vector<string> lines, int matrix_size){
    vector<int> buff, temp, null;
    vector<string> nullS, last;
    vector<vector<int>> ret;
    string mendStr;
    int commas = 0;

    for(int i = 3; i < lines.size(); i++){
        if(int n = lines[i].find("end") != string::npos)
        {
            last = splitToStr(lines[i], ',');
            ret.push_back(splitToInt(vecToString<string>(splitVec<string>(last, nullS, n)), ','));
            break;
        }
        commas = count_occ(lines[i], ',');
        if(commas < matrix_size - 1) {
            mendStr += lines[i] + lines[i+1];
            splitToInt(mendStr, ',');
            MyClientHandler::append<int>(buff, splitToInt(lines[i], ','));
            i++;
        }

        MyClientHandler::append<int>(buff, splitToInt(lines[i], ','));
        if(buff.size() > matrix_size){
            temp = splitVec<int>(buff, null, matrix_size);
            ret.push_back(temp);
            buff = temp;
        }
        else if(buff.size() == matrix_size){
            ret.push_back(buff);
        }
    }
    return ret;
}

/**
 * Gets a client request opening a socket using the sockfd we received as argument.
 * Then resolves it using its solver and cachemanager member.
 * @param sockfd
 */
void MyClientHandler::handleClient(int sockfd) {
    char bufferIn[11];
    string entry, all_entry;
    int matrix_size = 0, buffer_size = 1025;
    vector<string> lines;
    vector<vector<int>> matrix;

    CacheManager<string, string> *ch = getCm();
    int n;
    string resp;
    bool end = false;
    vector<int> null;

    while (!end) {
        bzero(bufferIn, buffer_size);
        n = (int) read(sockfd, bufferIn, buffer_size);

        if (n < 0) {
            perror("ERROR reading from socket");
            pthread_exit(NULL);
        }
        entry = string(bufferIn);

        all_entry += entry;

        if (lines[lines.size()].find("end") != string::npos) { //Check if the user wants to end the transmission.
            end = true;
            break;
        }
        append(lines, splitToStr(entry, '\r\n'));
    }
    matrix_size = atoi(lines[0].c_str());
    vector<int> a = splitToInt(lines[1], ',');
    vector<int> b = splitToInt(lines[2], ',');
    pair<int, int> src = make_pair(a[0], a[1]);
    pair<int, int> dst = make_pair(b[0], b[1]);


    matrix = processLines(lines, matrix_size);

    SearchableMatrix *s_matrix = new SearchableMatrix(matrix, src, dst);

    SearchResult sResult = solver->solve(s_matrix);

    n = send(sockfd, ((sResult.shortestRoute)).c_str(), strlen((sResult.shortestRoute).c_str()), 0);

    ch->saveDataInCache(bufferIn,sResult.shortestRoute);

    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }
}


MyClientHandler::MyClientHandler(CacheManager<string, string> *cm, Solver<Searchable *, SearchResult> *solver) : cm(cm),
                                                                                                                 solver(solver) {}

//
// Created by einav on 16/01/19.
//

#ifndef NEW_MILESTONE_2_FILESCOMPERALGO_H
#define NEW_MILESTONE_2_FILESCOMPERALGO_H

#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>

#include "StringReverser.h"
#include "MySerialServer.h"
#include "FileCacheManager.h"
#include "MyTestClientHandler.h"
#include "SearchableMatrix.h"
#include "SearcherSolver.h"
#include "DFS.h"
#include "BestFirstSearch.h"
#include "BFS.h"
#include "AStar.h"
using namespace server_side;
using std::fstream;
using std::vector;
using std::pair;
using std::to_string;

class FilesWriterAlgo{

    void writeDataToFile(string nameOfInputFile, string dataToWrite) {

        fstream stream;
        stream.open(nameOfInputFile, ios::app | ios::ate);

        stream << dataToWrite;

        stream.flush();
        stream.close();
    }

    void graphFormat(string developedVerFile, string weightOfPathFile,
                     SearchResult result, unsigned matrixSize){

        writeDataToFile(developedVerFile,
                            "{ x: " + std::to_string(matrixSize) +
                            ", y: " + to_string(result.developedVertices) + " },\n");

        writeDataToFile(weightOfPathFile,
                            "{ x: " + std::to_string(matrixSize) +
                            ", y: " + to_string(result.shortestWeight) + " },\n");

    }

    std::vector<std::vector<int>> createBaseMatrix(unsigned n){

        vector<vector<int>> vec;

        for (int k = 0; k < n; ++k) {
            vector<int> curLine;
            for (int i = 0; i < n; ++i) {
                curLine.push_back(rand() % 10);
            }
            vec.push_back(curLine);
        }

        return vec;
    }

    SearchResult AstarSolution(vector<vector<int>> matrix) {

        pair<int, int> source = {0, 0};
        pair<int, int> dest = {matrix.size() - 1, matrix.size() - 1};

        auto graph = new SearchableMatrix(matrix, source, dest);

        auto solver = new SearcherSolver(new AStar());
        auto result = solver->solve(graph);

        graphFormat("Astar_size_developed.txt", "Astar_size_weight.txt", result, matrix.size());

        return result;

    }

    SearchResult BFSSolution(vector<vector<int>> matrix) {

        pair<int, int> source = {0, 0};
        pair<int, int> dest = {matrix.size() - 1, matrix.size() - 1};

        auto graph = new SearchableMatrix(matrix, source, dest);

        auto solver = new SearcherSolver(new BFS());
        auto result = solver->solve(graph);

        graphFormat("bfs_size_developed.txt", "bfs_size_weight.txt", result, matrix.size());

        return result;


    }

    SearchResult DFSSolution(vector<vector<int>> matrix) {

        pair<int, int> source = {0, 0};
        pair<int, int> dest = {matrix.size() - 1, matrix.size() - 1};

        auto graph = new SearchableMatrix(matrix, source, dest);

        auto solver = new SearcherSolver(new DFS());


        auto result = solver->solve(graph);

        graphFormat("dfs_size_developed.txt", "dfs_size_weight.txt", result, matrix.size());

        return result;
    }

    SearchResult BestFirstSearchSolution(vector<vector<int>> matrix) {

        pair<int, int> source = {0, 0};
        pair<int, int> dest = {matrix.size() - 1, matrix.size() - 1};

        auto graph = new SearchableMatrix(matrix, source, dest);

        auto solver = new SearcherSolver(new BestFirstSearch());



        auto result = solver->solve(graph);

        graphFormat("best_size_developed.txt", "best_size_weight.txt", result, matrix.size());

        return result;
    }



    void allSolutions(vector<vector<int>> matrix) {

        auto best = BestFirstSearchSolution(matrix);
        auto dfs = DFSSolution(matrix);
        auto bfs = BFSSolution(matrix);
        auto AStar = AstarSolution(matrix);

        std::string allMatrixSolutions = std::to_string(best.shortestWeight) + "," +
                                         to_string(best.developedVertices) +
                                         "\n" + std::to_string(dfs.shortestWeight) +
                                         "," + to_string(dfs.developedVertices) +
                                         "\n" + std::to_string(bfs.shortestWeight) + "," +
                                         to_string(bfs.developedVertices) +
                                         "\n" + std::to_string(AStar.shortestWeight) + ","
                                         + to_string(AStar.developedVertices) + "\n";

        writeDataToFile("solution.txt", allMatrixSolutions);
    }


    void writeMatrixToFile(vector<vector<int>> matrix){

        string size = std::to_string(matrix.size());
        string src = "0,0";
        string dst = std::to_string(matrix.size() - 1) + "," + std::to_string(matrix.size() - 1);

        fstream stream("graphs.txt", std::ios::app);

        stream << size << "\n" << src << "\n" << dst << "\n";

        for (auto row: matrix){
            for (auto it = row.begin();it != row.end(); it++){
                if (it + 1 != row.end())
                    stream << *it << ",";
                else
                    stream << *it;
            }
            stream << "\n";
        }
        stream.close();
    }

public:

    void generateFiles() {

        // the requested size
        int size = 10;

        //number of matrix to generate
        writeDataToFile("graphs.txt", to_string(size) + "\n");

        for (int i = 1; i <= 10; i++) {

            vector<std::vector<int>> matrix = createBaseMatrix(size);

            writeMatrixToFile(matrix);
            allSolutions(matrix);

            size += 4;
        }

    }

};

#endif //NEW_MILESTONE_2_FILESCOMPERALGO_H

//
// Created by einav on 15/01/19.
//

#ifndef NEW_MILESTONE_2_STRUCTUREOFSEARCHRES_H
#define NEW_MILESTONE_2_STRUCTUREOFSEARCHRES_H

#include <string>
#include <vector>
using std:: vector;
using std:: string;

    enum Direction {

        NotSet = 0,
        Start = 1,
        Left = 2,
        Up = 3,
        Right = 4,
        Down = 5,
    };

    //the state of searchable structer result
    class State {

    public:

        State *top;
        State *bottom;
        State *left;
        State *right;

        int weigth;
        bool isInfinity;
        bool isMarked;
        Direction commingFrom;
        unsigned int indexOfRow;
        unsigned int indexOfCol;

        State(int weight){
            top=NULL;
            bottom=NULL;
            left=NULL;
            right=NULL;
            isMarked= false;
            weight=weight;
        };

        //return vec of the neighbors of vertices
        vector<State *> getNeighbors() {
            vector<State *> neighborsVec;

            if (bottom != NULL)
                neighborsVec.push_back(bottom);
            if (top != NULL)
                neighborsVec.push_back(top);
            if (left != NULL)
                neighborsVec.push_back(left);
            if (right != NULL)
                neighborsVec.push_back(right);
            return neighborsVec;
        }

    };

    struct SearchResult {

        string shortestRoute;

        int shortesWeight;

        int visitedVertices;

    };

#endif //NEW_MILESTONE_2_STRUCTUREOFSEARCHRES_H

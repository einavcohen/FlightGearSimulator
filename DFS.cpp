//
// Created by einav on 15/01/19.
//

#include "DFS.h"

    bool DFS::searchByDFS(State *currState){

    //cases we breaks the search

    if(currState == NULL){ return false; }

    if(currState->isInfinity){ return false; }

    if(currState->isVisited){ return false; }

    //sum the weigth of all the states
    searchResult.shortestWeight += currState->weigth;

    searchResult.developedVertices++;

    //if we reach here, we reach the goal, end of the search
    if(currState == stateOfgoal) { return true; }

    //remark the currstate as visited
    currState->isVisited = true;

    //we are making a recursive search DFS on all the satae in the
    // given searchable structure. in order to determain the direction of the
    //search in every step until reaching the goal state.

    //boolean variable to save the recursive result on state
    bool isPositive= false;

    //checking all the fourth direction-

    //top!=NULL
    if(currState->top!=NULL){
        isPositive = searchByDFS(currState->top);
        if(isPositive){
            this->searchResult.shortestRoute.insert(0, "Up, ");
            return true;
        }
    }

    //bottom!=NULL
    if (currState->bottom!=NULL){
        isPositive = searchByDFS(currState->bottom);
        if(isPositive) {
            this->searchResult.shortestRoute.insert(0, "Down, ");
            return true;
        }
    }

    //left!=NULL
    if(currState->left!=NULL){
        isPositive = searchByDFS(currState->left);
        if(isPositive){
            this->searchResult.shortestRoute.insert(0, "Left, ");
            return true;
        }
    }

    //right!=NULL
    if(currState->right!=NULL){
        isPositive = searchByDFS(currState->right);
        if(isPositive){
            this->searchResult.shortestRoute.insert(0, "Right, ");
            return true;
        }
    }

    searchResult.shortestWeight -= currState->weigth;

    return false;
}

SearchResult DFS:: search (Searchable *searchable ) {

    //initialize the search result before fill that struct
    searchResult.shortestWeight = 0;
    searchResult.shortestRoute = "";
    searchResult.developedVertices = 0;

    //goal state
    stateOfgoal = searchable->getGoalState();

    //that search func works about the searchable structure
    //and start from the start state of it.
    searchByDFS(searchable->getStartState());

    //finally, return the result of the search in a struct
    return this->searchResult;
}


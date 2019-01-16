//
// Created by einav on 16/01/19.
//

#include "AStar.h"
#include <queue>
#include <algorithm>

template<typename T, typename priority_t>

struct PriorityQueue {
    typedef std::pair<priority_t, T> PQElement;
    std::priority_queue<PQElement, std::vector<PQElement>,
            std::greater<PQElement>> elements;

    inline bool empty() const {
        return elements.empty();
    }

    inline void put(T item, priority_t priority) {
        elements.emplace(priority, item);
    }

    T get() {
        T best_item = elements.top().second;
        elements.pop();
        return best_item;
    }
};

inline int heuristicFunction(State *firstState, State *secondState) {
    return std::abs((int) (firstState->indexOfRow - secondState->indexOfRow)) +
           std::abs(((int) (firstState->indexOfCol - secondState->indexOfCol)));
}

SearchResult AStar:: search(Searchable *searchable) {

        //initialize the search result before fill that struct

        searchResult.developedVertices = 0;
        searchResult.shortestRoute = "";
        searchResult.shortestWeight = 0;

        //startState state on the searchable structure
        auto startState = searchable->getStartState();

        //goalState state
        auto goalState = searchable->getGoalState();
        //create that  map in order to save the last
        //location or state in the searchable structure
        std::map<State *, State *> cameFrom;

        //create that  map in order to save the cost of the
        //state we visit untill currState state in the searchable structure
        std::map<State *, int> currCost;

        //our priority queue, map between the states
        //and integers in the priority queue
        PriorityQueue<State *, int> frontOfQueue;
        frontOfQueue.put(startState, 0);
        //initialize start state
        cameFrom[startState] = startState;
        //current cost of a state
        currCost[startState] = 0;

        State *currState = NULL;

        //continue until the queue is empty
        while (!frontOfQueue.empty()) {
            currState = frontOfQueue.get();

            if (currState == goalState){break;}

            for (State *nextState : currState->getNeighbors()) {
                if (nextState->isInfinity){continue;}
                //sum all the costs
                int newCost = currCost[currState] + nextState->weigth;
                //
                if (currCost.find(nextState) == currCost.end() || newCost < currCost[nextState]){
                    currCost[nextState] = newCost;

                    int priority = newCost + heuristicFunction(nextState, goalState);

                    frontOfQueue.put(nextState, priority);
                    cameFrom[nextState] = currState;
                    searchResult.developedVertices++;
                }
            }

        }

        //the vector represent the path of states
        std::vector<State *> path;

        //if we reach here, no path exists
        if (currState != goalState) {
            searchResult.shortestRoute = "";
            searchResult.shortestWeight = -1;
            return searchResult;
        }

        //if we did not reach the start state,
        //we go on the structure and sum the weigth of
        //all the states we visit in
        while (currState != startState) {
            path.push_back(currState);
            currState = cameFrom[currState];
            searchResult.shortestWeight += currState->weigth;
        }
        //reach the start state
        path.push_back(startState);
        //revers the states in the path we found after the progress above
        std::reverse(path.begin(), path.end());

        std::string stepOnPath;


        //start the iteration according to the path we found
        //and travel all the states in it in order to restore the path

        for (auto location = path.begin(); location != path.end() && location + 1 != path.end();location++) {
            //stepOnPath down in path
            if ((*(location + 1))->indexOfRow > (*(location))->indexOfRow){stepOnPath = "Down, ";}
            //stepOnPath up in path
            if ((*(location + 1))->indexOfRow < (*(location))->indexOfRow){stepOnPath = "Up, ";}
            //stepOnPath left side of path
            if ((*(location + 1))->indexOfCol < (*(location))->indexOfCol){stepOnPath = "Left, ";}
            //stepOnPath right side of path
            if ((*(location + 1))->indexOfCol > (*(location))->indexOfCol) {stepOnPath = "Right, ";}
            //append the current stepOnPath to the final path of the searchable structure
            searchResult.shortestRoute.append(stepOnPath);
        }

        searchResult.shortestRoute =
                searchResult.shortestRoute.substr(0, searchResult.shortestRoute.length() - 2);

        return searchResult;
    }

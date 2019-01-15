//
// Created by einav on 15/01/19.
//

#ifndef NEW_MILESTONE_2_DFS_H
#define NEW_MILESTONE_2_DFS_H

#include "queue"
#include "Searcher.h"

class DFS : public Searcher {

private:
    SearchResult searchResult;

    //goal state
    State *stateOfgoal;

    bool searchByDFS(State *currState);

public:
    SearchResult search (Searchable *searchable )override;

};


#endif //NEW_MILESTONE_2_DFS_H

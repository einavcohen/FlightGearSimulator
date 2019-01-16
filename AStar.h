//
// Created by einav on 16/01/19.
//

#ifndef NEW_MILESTONE_2_ASTAR_H
#define NEW_MILESTONE_2_ASTAR_H

#include <map>
#include "Searcher.h"

class AStar : public Searcher {

private:

    SearchResult searchResult;

public:
    SearchResult search(Searchable *searchable) override;
};


#endif //NEW_MILESTONE_2_ASTAR_H

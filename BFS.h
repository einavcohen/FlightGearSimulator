//
// Created by einav on 15/01/19.
//

#ifndef NEW_MILESTONE_2_BFS_H
#define NEW_MILESTONE_2_BFS_H

#include "queue"
#include "Searcher.h"

class BFS : public Searcher {

    public:
        SearchResult search (Searchable *searchable )override;
};


#endif //NEW_MILESTONE_2_BFS_H

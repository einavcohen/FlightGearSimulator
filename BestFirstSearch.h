//
// Created by einav on 15/01/19.
//

#ifndef NEW_MILESTONE_2_BESTFIRSTSEARCH_H
#define NEW_MILESTONE_2_BESTFIRSTSEARCH_H

#include "Searcher.h"

class BestFirstSearch: public Searcher {

public:
    SearchResult search (Searchable *searchable ) override;

};



#endif //NEW_MILESTONE_2_BESTFIRSTSEARCH_H

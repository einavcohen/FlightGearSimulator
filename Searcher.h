//
// Created by einav on 15/01/19.
//

#ifndef NEW_MILESTONE_2_SEARCHER_H
#define NEW_MILESTONE_2_SEARCHER_H

#include "StructSearchResult.h"
#include "Searchable.h"

class Searcher {

public:

    //searchs on the searchable structure
    virtual SearchResult search(Searchable *searchable) = 0;
    //distructor
    virtual ~Searcher() = default;
};

#endif //NEW_MILESTONE_2_SEARCHER_H

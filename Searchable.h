//
// Created by einav on 15/01/19.
//

#ifndef NEW_MILESTONE_2_SEARCHABLE_H
#define NEW_MILESTONE_2_SEARCHABLE_H

#include <vector>
#include "StructSearchResult.h"

using std::vector;

    class Searchable {

    public:

        virtual State *getStartState() = 0;

        virtual State *getGoalState() = 0;

        //all the states we can reach from given state
        virtual vector<State *> getAllPossibleStates(State *state) = 0;

    };


#endif //NEW_MILESTONE_2_SEARCHABLE_H

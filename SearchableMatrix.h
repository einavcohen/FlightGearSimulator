//
// Created by einav on 15/01/19.
//

#ifndef NEW_MILESTONE_2_SEARCHABLEMATRIX_H
#define NEW_MILESTONE_2_SEARCHABLEMATRIX_H
#include "Searchable.h"
using std::vector;
using std::pair;


class SearchableMatrix : public Searchable{
    private:
        State *startState;
        State *destState;

    public:

        vector<vector<State>> matrix;

        SearchableMatrix(vector<vector<int>> inputMatrix, pair<int, int> src, pair<int, int> dst);

        State *getStartState() override;

        State *getGoalState() override;

         //neighbors of a given state
        vector<State *> getAllPossibleStates(State *s) override;

};

#endif //NEW_MILESTONE_2_SEARCHABLEMATRIX_H

//
// Created by einav on 15/01/19.
//

#ifndef NEW_MILESTONE_2_SEARCHERSOLVER_H
#define NEW_MILESTONE_2_SEARCHERSOLVER_H

#include <string>
#include "Solver.h"
#include "Searcher.h"

using std::string;

 //object adapter - enables to define a solver with searching skills

    class SearcherSolver : public Solver<Searchable *, SearchResult> {

        Searcher *searcher;


    public:

        SearcherSolver(Searcher *searcher) : searcher(searcher) {}

        SearchResult solve(Searchable *p) override {
            return searcher->search(p);
        }

        ~SearcherSolver() override {
            delete(searcher);
        }

    };

#endif //NEW_MILESTONE_2_SEARCHERSOLVER_H

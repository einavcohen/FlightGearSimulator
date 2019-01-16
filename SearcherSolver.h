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

        void * operator new(size_t size, Searcher *searcher)
        {
            void * p = ::new SearcherSolver(searcher);
            //void * p = malloc(size); will also work fine
            Solver *pTag = static_cast<Solver<Searchable *, SearchResult> *>(p);

            return pTag;
        }

        SearchResult solve(Searchable *p) override {
            return searcher->search(p);
        }

        ~SearcherSolver() {
            delete(searcher);
        }
    };

#endif //NEW_MILESTONE_2_SEARCHERSOLVER_H

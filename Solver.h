//
// Created by einav on 10/01/19.
//

#ifndef MILESTONE_2_SOLVER_H
#define MILESTONE_2_SOLVER_H
using namespace std;

template <class Problem, class Solution>

class Solver {

    public:
        //solve method to solve the problem
        virtual Solution solve(Problem) = 0;
        //distructor
        virtual ~Solver() = default;

    };

#endif //MILESTONE_2_SOLVER_H

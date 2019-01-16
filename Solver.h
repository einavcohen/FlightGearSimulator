//
// Created by newbuntu on 09/01/19.
//

#ifndef UNTITLED1_SOLVER_H
#define UNTITLED1_SOLVER_H
using namespace std;

template <class S, class P>
class Solver {
public:
    virtual P solve(S Problem) = 0;
};

#endif //UNTITLED1_SOLVER_H

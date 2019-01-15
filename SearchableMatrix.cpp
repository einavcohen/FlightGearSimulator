#include <iostream>
#include "SearchableMatrix.h"


State * SearchableMatrix::getStartState(){
    return this->startState;
}

State * SearchableMatrix:: getGoalState() {
    return this->destState;
}


vector<State *> SearchableMatrix::getAllPossibleStates(State *s) {
    return s->getNeighbors();
}


SearchableMatrix::SearchableMatrix(vector<vector<int>> inputMatrix,
        pair<int, int> src, pair<int, int> dst) :
              matrix(inputMatrix.size(),
              vector<State>(inputMatrix[0].size(),State(0))) {

    int sizeOfRows = inputMatrix.size();
    int sizeOfCols = inputMatrix[0].size();

    //build the matrix
    for (int i = 0; i < sizeOfRows; ++i) {
        for (int j = 0; j < sizeOfCols; ++j) {
            int currWeigth = inputMatrix[i][j];
            matrix[i][j].weigth = currWeigth;
        }
    }

    //init all states
    for (int i = 0; i < sizeOfRows; ++i) {

        for (int j = 0; j < sizeOfCols; ++j) {

            State *currState = &matrix[i][j];

            currState->commingFrom = NotSet;

            currState->isMarked = false;

            if (currState->weigth == -1) {
                currState->isInfinity = true;
            } else {
                currState->isInfinity = false;
            }

            //up != null
            if (i != 0) {
                &matrix[i - 1][j];
            } else {
                currState->top = NULL;
            }
            //bottom != null
            if (i != (sizeOfRows - 1)) {
                &matrix[i + 1][j];
            } else {
                currState->bottom = NULL;
            }
            //left != null
            if (j != 0) {
                &matrix[i][j - 1];
            } else {
                currState->left = NULL;
            }
            //right != null
            if (j != (sizeOfCols - 1)) {
                &matrix[i][j + 1];
            } else {
                currState->right = NULL;
            }

            currState->indexOfRow = i;
            currState->indexOfCol = j;

            //init the start state
            if (i == src.first && j == src.second) {
                startState = &matrix[i][j];
            }

            //init the end state
            if (i == dst.first && j == dst.second) {
                destState = &matrix[i][j];
            }

        }

    }

}


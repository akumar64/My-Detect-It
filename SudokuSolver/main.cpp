//
//  main.cpp
//  SudokuSolver
//
//  Created by ARJUN KUMAR on 8/27/17.
//  Copyright © 2017 ARJUN KUMAR. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

void changePossibleFromConstraints(bool doFindPossible, int setNum, int changeRow, int changeCol, vector<vector<vector<bool> > >& boardPossible, vector<vector<int> >& boardNumPossible, vector<vector<char> >& board, int& numKnown)
{
    int finalSetNum = setNum;
    if (doFindPossible)
    {
        for (int numInd = 0; numInd < 9; numInd++)
        {
            if (boardPossible.at(changeRow).at(changeCol).at(numInd))
            {
                finalSetNum = numInd+1;
                break;
            }
        }
    }
    cout << "changeRow " << changeRow << " changeCol " << changeCol << " setNum " << finalSetNum << endl;
    if (board.at(changeRow).at(changeCol) != '.' && doFindPossible)
    {
        cout << "editing original" << endl;
    }
    if (doFindPossible)
    {
        board.at(changeRow).at(changeCol) = '0'+finalSetNum;
    }
    boardNumPossible.at(changeRow).at(changeCol) = 0;
    numKnown++;
    
    for (int colI = 0; colI < 9; colI++)
    {
        if (colI != changeCol)
        {
            if (boardPossible.at(changeRow).at(colI).at(finalSetNum-1))
            {
                boardPossible.at(changeRow).at(colI).at(finalSetNum-1) = false;
                boardNumPossible.at(changeRow).at(colI) = boardNumPossible.at(changeRow).at(colI)-1;
                if (boardNumPossible.at(changeRow).at(colI) == 1)
                {
                    changePossibleFromConstraints(true, 0, changeRow, colI, boardPossible, boardNumPossible, board, numKnown);
                }
            }
        }
    }
    for (int rowI = 0; rowI < 9; rowI++)
    {
        if (rowI != changeRow)
        {
            if (boardPossible.at(rowI).at(changeCol).at(finalSetNum-1))
            {
                boardPossible.at(rowI).at(changeCol).at(finalSetNum-1) = false;
                boardNumPossible.at(rowI).at(changeCol) = boardNumPossible.at(rowI).at(changeCol)-1;
                if (boardNumPossible.at(rowI).at(changeCol) == 1)
                {
                    changePossibleFromConstraints(true, 0, rowI, changeCol, boardPossible, boardNumPossible, board, numKnown);
                }
            }
        }
    }
    int rowSquareInd = changeRow/3;
    int colSquareInd = changeCol/3;
    
    for (int rowI = rowSquareInd*3; rowI < (rowSquareInd+1)*3; rowI++)
    {
        for (int colI = colSquareInd*3; colI < (colSquareInd+1)*3; colI++)
        {
            if (rowI != changeRow || colI != changeCol)
            {
                if (boardPossible.at(rowI).at(colI).at(finalSetNum-1))
                {
                    boardPossible.at(rowI).at(colI).at(finalSetNum-1) = false;
                    boardNumPossible.at(rowI).at(colI) = boardNumPossible.at(rowI).at(colI)-1;
                    if (boardNumPossible.at(rowI).at(colI) == 1)
                    {
                        changePossibleFromConstraints(true, 0, rowI, colI, boardPossible, boardNumPossible, board, numKnown);
                    }
                }
            }
        }
    }
}

void solveSudoku(vector<vector<char> >& board)
{
    vector<bool> possibleNum(9, true);
    vector<vector<bool> > rowPosslbe(9, possibleNum);
    vector<vector<vector<bool> > > boardPossible(9, rowPosslbe);
    
    vector<int> rowNumPossible(9, 9);
    vector<vector<int> > boardNumPossible(9, rowNumPossible);
    
    int numKnown = 0;
    
    for (int rowI = 0; rowI < 9; rowI++)
    {
        for (int colI = 0; colI < 9; colI++)
        {
            if (board.at(rowI).at(colI) != '.')
            {
                changePossibleFromConstraints(false, board.at(rowI).at(colI)-'0', rowI, colI, boardPossible, boardNumPossible, board, numKnown);
            }
        }
    }
    cout << "num known " << numKnown << endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "Hello, World!\n";
    
    char board[9][9] = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    
    vector<char> boardRow(9);
    vector<vector<char> > charBoard(9, boardRow);
    
    for (int rowI = 0; rowI < 9; rowI++)
    {
        for (int colI = 0; colI < 9; colI++)
        {
            charBoard.at(rowI).at(colI) = board[rowI][colI];
        }
    }
    
    int testN = 5;
    char testC = '0'+testN;
    
    cout << testC << endl;
    
    solveSudoku(charBoard);
    int checkBoard = 0;
    return 0;
}

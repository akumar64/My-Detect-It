//
//  main.cpp
//  FlattenField
//
//  Created by ARJUN KUMAR on 8/26/17.
//  Copyright © 2017 ARJUN KUMAR. All rights reserved.
//

#include <iostream>
#include <vector>
#include <array>
#include <queue>

using namespace std;

int findMinTree(int **field, int numRows, int numColumns, int prevMin, int& newRow, int& newCol)
{
    // can also use hash table to store where the tallest trees are
    int newMinTreeHeight = INT_MAX;
    for (int rowI = 0; rowI < numRows; rowI++)
    {
        for (int colI = 0; colI < numColumns; colI++)
        {
            if (field[rowI][colI] > prevMin)
            {
                if (field[rowI][colI] < newMinTreeHeight)
                {
                    newRow = rowI;
                    newCol = colI;
                    newMinTreeHeight = field[rowI][colI];
                }
            }
        }
    }
    cout << newMinTreeHeight << endl;
    cout << newRow << endl;
    cout << newCol << endl;
    return newMinTreeHeight;
}


struct CustomCompare
{
    int destinationRow;
    int destinationCol;
    
    struct CustomCompare* customComparePtr = new CustomCompare;
    CustomCompare* customComparePtr2 = new CustomCompare;
    
    CustomCompare()
    {
    }
    
    CustomCompare(int a, int b)
    {
        destinationCol = a;
        destinationRow = b;
    }
    
    bool operator()(const array<int, 3>& lhs, const array<int, 3>& rhs)
    {
        return (abs(destinationRow-lhs[0])+abs(destinationCol-lhs[1])) > (abs(destinationRow-rhs[0])+abs(destinationCol-rhs[1])); // opposite sign to get min distance on top as opposed to max
    }
};

bool isAllowed(int **field, int numRows, int numCols, int rowI, int colI, int destinationHeight)
{
    if (rowI < numRows && rowI >= 0 && colI >= 0 && colI < numCols)
    {
        if (field[rowI][colI] == 1 || field[rowI][colI] == destinationHeight)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

int findPathToNextMin(int **field, int numRows, int numCols, int currentRow, int currentCol, int destinationRow, int destinationCol, int destinationHeight)
{
    vector<vector<bool> > isVisited(numRows);
    for (int rowI = 0; rowI < numRows; rowI++)
    {
        vector<bool> colVec(numCols, false);
        isVisited.at(rowI) = colVec;
    }
    
    priority_queue<CustomCompare, vector<CustomCompare>, CustomCompare> testPriQueue;
    
    array<int, 3> currentLocation = {currentRow, currentCol, 0};
    
    typedef priority_queue<array<int, 3>, vector<array<int, 3> >, CustomCompare> PrQueueLocType;
    
    CustomCompare* testPtr = new CustomCompare(2, 3);
    shared_ptr<CustomCompare> testPtr2(new CustomCompare(2, 3));
    
    CustomCompare distanceCompare;
    distanceCompare.destinationCol = destinationCol;
    distanceCompare.destinationRow = destinationRow;
    PrQueueLocType prQueue(distanceCompare);
    //prQueue.push(currentLocation);
    
    array<int, 3> locationI(currentLocation);
    bool isFound = true;
    cout << "d row " << destinationRow << endl;
    cout << "d col " << destinationCol << endl;
    //cout << (locationI[0] != destinationRow) << endl;
    isVisited.at(currentRow).at(currentCol) = true;
    while (locationI[0] != destinationRow || locationI[1] != destinationCol)
    {
        cout << "pr rowI " << locationI[0] << endl;
        cout << "pr colI " << locationI[1] << endl;
        
        array<array<int, 3>, 4> deltaLocationS;
        deltaLocationS[0] = {locationI[0]-1, locationI[1], locationI[2]+1};
        deltaLocationS[1] = {locationI[0]+1, locationI[1], locationI[2]+1};
        deltaLocationS[2] = {locationI[0], locationI[1]-1, locationI[2]+1};
        deltaLocationS[3] = {locationI[0], locationI[1]+1, locationI[2]+1};
        
        for (int deltaI = 0; deltaI < 4; deltaI++)
        {
            int deltaRow = deltaLocationS[deltaI][0];
            int deltaCol = deltaLocationS[deltaI][1];
            if (isAllowed(field, numRows, numCols, deltaRow, deltaCol, destinationHeight))
            {
                if (!isVisited.at(deltaRow).at(deltaCol))
                {
                    isVisited.at(deltaRow).at(deltaCol) = true;
                    prQueue.push(deltaLocationS[deltaI]);
                }
            }
        }
        if (prQueue.empty())
        {
            isFound = false;
            break;
        }
        else
        {
            locationI = prQueue.top();
            prQueue.pop();
        }
    }
    if (isFound)
    {
        return locationI[2];
    }
    else
    {
        return -1;
    }
}

int cornerLevelFeild(int numRows, int numColumns, int **field)
{
    int firstRow = 0;
    int firstCol = 0;
    int minTreeHeight = findMinTree(field, numRows, numColumns, 1, firstRow, firstCol);
    cout << firstCol << endl;
    
    int cornerRows[4] = {0, 0, numRows-1, numRows-1};
    int cornerCols[4] = {0, numColumns-1, 0, numColumns-1};
    
    int finalFirstPath = INT_MAX;
    int startCornerI = -1;
    for (int cornerI = 0; cornerI < 4; cornerI++)
    {
        if (field[cornerRows[cornerI]][cornerCols[cornerI]] == 1)
        {
            int firstPath = findPathToNextMin(field, numRows, numColumns, cornerRows[cornerI], cornerCols[cornerI], firstRow, firstCol, minTreeHeight);
            cout << "path " << firstPath << endl;
            if (firstPath > -1)
            {
                if (firstPath < finalFirstPath)
                {
                    finalFirstPath = firstPath;
                    startCornerI = cornerI;
                }
            }
        }
    }
    cout << "start cor " << startCornerI << endl;
    if (finalFirstPath < INT_MAX)
    {
        field[firstRow][firstCol] = 1;
        
        int currentRow = firstRow;
        int currentCol = firstCol;
        int totalPath = finalFirstPath;
        
        int newRowI = 0;
        int newColI = 0;
        int treeSize = findMinTree(field, numRows, numColumns, minTreeHeight, newRowI, newColI);
        
        bool isFoundI = true;
        while (treeSize < INT_MAX)
        {
            int newPath = findPathToNextMin(field, numRows, numColumns, currentRow, currentCol, newRowI, newColI, treeSize);
            
            if (newPath > -1)
            {
                currentRow = newRowI;
                currentCol = newColI;
                totalPath = totalPath+newPath;
                field[newRowI][newColI] = true;
                
                treeSize = findMinTree(field, numRows, numColumns, treeSize, newRowI, newColI);
            }
            else
            {
                isFoundI = false;
                break;
            }
        }
        if (isFoundI)
        {
            return totalPath;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    int numRows = 3;
    int numColumns = 4;
    int** field = new int*[numRows];
    for (int rowI  = 0; rowI < numRows; rowI++)
    {
        field[rowI] = new int[numColumns];
    }
    
//    int inputField[3][4] = {{1, 3, 0, 2}, {1, 1, 1, 1}, {1, 1, 1, 5}};
    int inputField[3][4] = {{3, 1, 0, 5}, {1, 1, 2, 1}, {1, 1, 0, 1}};
    
    for (int rowI = 0; rowI < numRows; rowI++)
    {
        for (int colI = 0; colI < numColumns; colI++)
        {
            field[rowI][colI] = inputField[rowI][colI];
        }
    }
    
    int answer = cornerLevelFeild(numRows, numColumns, field);
    cout << "answer " << answer << endl;

    
    return answer;
}

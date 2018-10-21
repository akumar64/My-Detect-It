//
//  main.cpp
//  ZigZagArray
//
//  Created by ARJUN KUMAR on 4/6/18.
//  Copyright © 2018 ARJUN KUMAR. All rights reserved.
//

/* Notes
 If end > start
    if middle is in between (and equal to start), max is at right
    if greater than end (or equal to end), max is either left or right
 
 opposite for other sign for end and start
 
 if equal, has to do both sides
 
 find max if section between two numbers is empty and just compare
 */

/* doing it this way is looking at log(n) + log(n/2) + log(n/4) + ... = O((log n)^2)
 better to do log indexing (n/2, 3n/4, 7n/8)  (saw an example of this in prep) or did I see 2, 4, 8 ...
 log indexing as described above is basically same as before
 2, 4, 8, ... is still O((log n)^2)
*/

/* can find which side, based on if increasing or decreasing
 * binary search ish was the way to go, picturing it will get to the answer
 * ya, use half-1, half, half+1, shoot, are duplicates allowed?
 * when picking a side, should include the edges
 */

// other problems:
// https://www.geeksforgeeks.org/category/algorithm/dynamic-programming/, contiguous array which doesn't have any elements from another array, or with max sum (practice these)
// will do median at work lol
// inorder node and is BST good tree examples
// paths with sums is also a good one

// need a dictionary example and a priority queue example too

#include <iostream>
#include <vector>

using namespace std;

int FindMaxRec(vector<int> &array, int startInd, int endInd)
{
    int halfInd = (startInd+endInd)/2;
    int halfVal = array.at(halfInd);
    if (halfInd > startInd && halfInd < endInd)
    {
        int leftVal = array.at(halfInd-1);
        int rightVal = array.at(halfInd+1);
        if (halfVal > leftVal && halfVal > rightVal)
        {
            return halfVal;
        }
        else if (rightVal > leftVal)
        {
            return FindMaxRec(array, halfInd, endInd);
        }
        else
        {
            return FindMaxRec(array, startInd, halfInd);
        }
    }
    else
    {
        int startVal = array.at(startInd);
        int endVal = array.at(endInd);
        if (startVal > endVal)
        {
            return startVal;
        }
        else
        {
            return endVal;
        }
    }
}

int FindMaxOfZigZagArray(vector<int> &array)
{
    return FindMaxRec(array, 0, array.size()-1);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    //std::cout << "Hello, World!\n";
    
    vector<int> zigZagArr = {1, 2, 3, 4, 5, 6, 7, 10, 7, 4, 1};
    
    int madVal = FindMaxOfZigZagArray(zigZagArr);
    cout << madVal << endl;
    
    return madVal;
}

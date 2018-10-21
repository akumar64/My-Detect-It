//
//  main.cpp
//  MinWindowSubstring
//
//  Created by ARJUN KUMAR on 8/30/17.
//  Copyright © 2017 ARJUN KUMAR. All rights reserved.
//

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <array>

using namespace std;

typedef unordered_map<char, array<int, 4>> HashType;

string minWindow(string s, string t)
{
    string minWindowStr = "";
    
    unordered_map<char, int> tHash;
    int tHashArr[128] = {0};
    unordered_map<char, int> sHash;
    int sHashArr[128] = {0};
    
    for (int ind = 0; ind < t.size(); ind++)
    {
        tHashArr[t[ind]] = tHashArr[t[ind]]+1;
        if (tHash.find(t[ind]) != tHash.end())
        {
            tHash[t[ind]] = tHash[t[ind]]+1;
        }
        else
        {
            tHash[t[ind]] = 1;
            sHash[t[ind]] = 0;
        }
    }
    
    int letterCounter = 0;
    int minLength = INT_MAX;
    
    vector<int> matchIndices(s.size());
    int solnI = 0;
    int addI = 0;
    
    for (int ind = 0; ind < s.size(); ind++)
    {
        if (tHash.find(s[ind]) != tHash.end())
        {
            if (sHash[s[ind]] < tHash[s[ind]])
            {
                letterCounter++;
            }
            sHashArr[s[ind]] = sHashArr[s[ind]]+1;
            sHash[s[ind]] = sHash[s[ind]]+1;
            
            matchIndices.at(addI) = ind;
            addI++;
            if (letterCounter == t.size())
            {
                while (letterCounter == t.size())
                {
                    int firstIndex = matchIndices[solnI];
                    int length = ind-firstIndex+1;
                    cout << "found " << s.substr(firstIndex, length) << endl;
                    if (length < minLength)
                    {
                        minWindowStr = s.substr(firstIndex, length);
                        minLength = length;
                    }
                    sHash[s[matchIndices.at(solnI)]] = sHash[s[matchIndices.at(solnI)]]-1;
                    if (sHash[s[matchIndices.at(solnI)]] < tHash[s[matchIndices.at(solnI)]])
                    {
                        letterCounter--;
                    }
                    solnI++;
                }
            }
        }
    }
    
    return minWindowStr;
}

array<int, 3> testFun(int b)
{
    int a = 1;
    
    if (a == 2) {
        
    } else {
        
    }
    return {};
}

struct TestStructInd
{
    int ind;
};

void testMethod(const int& intConstRef, int& intRef)
{
    //compile error if change const ref
    int copyIntRef = intRef;
    copyIntRef++; // yes, doesn't change intRef
    intRef++;
}

int main(int argc, const char * argv[]) {
    int* testArr = new int[10];
    shared_ptr<int> testArr2(new int[10]);
    //testArr2[1] = 5;
    //int testNum = 1;
    vector<int> vecTest(10);
    vector<vector<int> > test2D(10, vecTest);
    int testNum = test2D.at(2).at(1);
    testNum = test2D[2][5];
    
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //string s = "ADOBECODEBANC";
    //string t = "ABC";
    string s = "ADAOBEACOAADAEBANCA";
    string t = "AABC";
    
    string minWindowStr = minWindow(s, t);
    cout << "answer " << minWindowStr << endl;
    
    // testing
    vector<int> sumVec(10, 0);
    TestStructInd structInd;
    vector<TestStructInd> indices(10, structInd);
    indices[1].ind = 3; indices[2].ind = 5; indices[3].ind = 3; indices[4].ind = 5;
    
    for (vector<TestStructInd>::iterator it = indices.begin(); it != indices.end(); ++it)
    {
        sumVec.at(it->ind)++;
    }
    
    for (int ind = 0; ind < sumVec.size(); ind++)
    {
        cout << sumVec.at(ind) << " ";
    }
    cout << endl;
    
    unordered_map<int, int> testDict;
    testDict = {{1, 3}};
    for (unordered_map<int, int>::iterator it = testDict.begin(); it != testDict.end(); ++it)
    {
        cout << it->first << " " << it->second << endl;
    }
    
    int constInt = 2;
    int intT = 4;
    testMethod(constInt, intT);
    
    cout << "int T " << intT << endl;
    
    double db = 5;
    
    bool checkWhole = abs(round(db)-db) < 0.001;
    cout << checkWhole << endl;

    int iNum = 5;
    int iDivNum = 2;
    cout << (double)iNum/iDivNum << endl;
    
    int a = 1, b = 1;
    
    cout << "a " << a << endl;
    
    return 0;
}

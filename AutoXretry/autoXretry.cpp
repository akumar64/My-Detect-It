//
//  autoXretry.cpp
//  CodingChallenge
//
//  Created by ARJUN KUMAR on 8/22/17.
//  Copyright © 2017 ARJUN KUMAR. All rights reserved.
//


#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

typedef unordered_map<char, int> operatorCountMapType;
typedef unordered_map<char, vector<int> > operatorIndicesMapType;

class OperatorEdge;
zz
class ParsedNum
{
public:
    
    float number;
    shared_ptr<OperatorEdge> leftOperator;
    shared_ptr<OperatorEdge> rightOperator;
    
public:
    ParsedNum()
    {
        
    }
    
    ParsedNum(float inNumber)
    {
        number = inNumber;
    }
};

class OperatorEdge
{
public:
    
    shared_ptr<ParsedNum> rightNumP;
    shared_ptr<ParsedNum> leftNumP;
    
    char opChar;
    
public:
    
    OperatorEdge()
    {
        
    }
    
    OperatorEdge(char inOpChar)
    {
        opChar = inOpChar;
    }
    
    float operate()
    {
        if (opChar == '&')
        {
            if (rightNumP->number > leftNumP->number)
            {
                return rightNumP->number;
            }
            else
            {
                return leftNumP->number;
            }
        }
        else if (opChar == '|')
        {
            if (rightNumP->number < leftNumP->number)
            {
                return rightNumP->number;
            }
            else
            {
                return leftNumP->number;
            }
        }
        else if (opChar == '*')
        {
            return leftNumP->number*rightNumP->number;
        }
        else if (opChar == '+')
        {
            return leftNumP->number+rightNumP->number;
        }
        else
        {
            return -100;
        }
    }
};



typedef vector<shared_ptr<OperatorEdge> > operatorEdgeVecType;

float OperateParsedString(string operatorOrder, operatorIndicesMapType& operatorIndices, operatorCountMapType& operatorCountS, operatorEdgeVecType& operatorVec, int totalOpCount)
{
    float answer = 0;
    for (string::iterator it = operatorOrder.begin(); it != operatorOrder.end(); ++it)
    {
//        cout << *it << endl;
        int opCount = operatorCountS[*it];
        vector<int> opIndices = operatorIndices[*it];
        
        for (int ind = 0; ind < opCount; ind++)
        {
            int opIndex = opIndices[ind];
            
            answer = operatorVec[opIndex]->operate();
            shared_ptr<ParsedNum> answerP(new ParsedNum(answer));
            
//            if (opIndex > 0)
            shared_ptr<OperatorEdge> leftOperator = operatorVec[opIndex]->leftNumP->leftOperator;
            if (leftOperator != nullptr)
            {
                leftOperator->rightNumP = answerP;
                answerP->leftOperator = leftOperator;
            }
            shared_ptr<OperatorEdge> rightOperator = operatorVec[opIndex]->rightNumP->rightOperator;
            if (rightOperator != nullptr)
            {
                rightOperator->leftNumP = answerP;
                answerP->rightOperator = rightOperator;
            }
        }
        
        cout << opCount << endl;
    }
    return answer;
}

int ParseWholeString(string wholeString, operatorCountMapType& operatorCountS, operatorIndicesMapType& operatorIndices, operatorEdgeVecType& operatorVec)
{
    string::size_type sz;
    
    size_t startPos = 0;
    size_t endPos = wholeString.find(' ');
    
    int operatorCounter = 0;
    while (endPos != string::npos)
    {
        float num = stof(wholeString.substr(startPos), &sz);
        cout << num << " , ";
        
        char operatorChar = wholeString[endPos+1];
        int prevOperatorCount = operatorCountS[operatorChar];
        (operatorIndices[operatorChar]).at(prevOperatorCount) = operatorCounter;
        operatorCountS[operatorChar] = prevOperatorCount+1;
        
        shared_ptr<OperatorEdge> opEdge(new OperatorEdge(operatorChar) );
        
        shared_ptr<ParsedNum> leftNum(new ParsedNum(num) );
        opEdge->leftNumP = leftNum;
        leftNum->rightOperator = opEdge;
        if (operatorCounter > 0)
        {
            (operatorVec[operatorCounter-1])->rightNumP = leftNum;
            leftNum->leftOperator = operatorVec[operatorCounter-1];
        }
        
        operatorVec.at(operatorCounter) = opEdge;
        
        startPos = endPos+3;
        endPos = wholeString.find(' ', startPos);
        operatorCounter++;
        
//        ParsedNum*  parsedNumTest = new ParsedNum(operatorCounter-1);
//        checkPtrVec[operatorCounter-1] = parsedNumTest;
    }
    float lastNum = stof(wholeString.substr(startPos), &sz);
    cout << lastNum << endl;
    shared_ptr<ParsedNum> lastNumP(new ParsedNum(lastNum));
    
    (operatorVec[operatorCounter-1])->rightNumP = lastNumP;
    lastNumP->leftOperator = operatorVec[operatorCounter-1];
    
    return operatorCounter;
}


int main()
{
    auto words = { "Hello, ", "World!", "\n" };
    for (const string& word : words)
    {
        cout << word;
    }
    
    vector<int>* testVec = new vector<int>(5);
    
    string inputTest = "4 + 1 & 2 * 7 | 3 + 6";
//    string inputTest = "4.5 + 1 & 2.23 * 7 | 3.234 + 6.1";
    
    operatorCountMapType opCountMap;
    opCountMap['&'] = 0;
    opCountMap['|'] = 0;
    opCountMap['*'] = 0;
    opCountMap['+'] = 0;
    
    operatorIndicesMapType opIndicesMap;
    vector<int> opIndices(inputTest.length());
    opIndicesMap['&'] = opIndices;
    opIndicesMap['|'] = opIndices;
    opIndicesMap['*'] = opIndices;
    opIndicesMap['+'] = opIndices;
    
    operatorEdgeVecType opEdgeVec(inputTest.length());
    
    //vector<ParsedNum*> checkPtrVec(inputTest.length());
    int totalOpCount = ParseWholeString(inputTest, opCountMap, opIndicesMap, opEdgeVec); //, checkPtrVec);
    
    //cout << "test ptr " << (checkPtrVec[1])->number << endl; // so what this showed was if define something in a method through stack Dog sparky('test'), pointer referencing not correct, had to instantiate through heap
    
    string operatorOrder = "&|*+";
    
    float finalResult = OperateParsedString(operatorOrder, opIndicesMap, opCountMap, opEdgeVec, totalOpCount);
    
    cout << "Final Result = " << finalResult << endl;
}

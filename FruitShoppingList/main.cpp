//
//  main.cpp
//  FruitShoppingList
//
//  Created by ARJUN KUMAR on 8/26/17.
//  Copyright © 2017 ARJUN KUMAR. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool fruitComparer(string fruitInList, string fruitInGroup)
{
    if (fruitInGroup.compare("anything") == 0)
    {
        return true;
    }
    else
    {
        if (fruitInGroup.compare(fruitInList) == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

int checkWinner(vector<vector<string> > codeList, vector<string> shoppingCart)
{
    int groupInd = 0;
    int fruitInd = 0;
    while (groupInd < codeList.size() && fruitInd < shoppingCart.size() )
    {
        int startFruit = fruitInd;
        int inFruitInd = fruitInd;
        int inGroupInd = 0;
        cout << "gI " << groupInd << endl;
        cout << "fI " << fruitInd << endl;
        while (fruitComparer(shoppingCart.at(inFruitInd), codeList.at(groupInd).at(inGroupInd)))
        {
            inFruitInd++;
            inGroupInd++;
            if (inFruitInd >= shoppingCart.size() || inGroupInd >= codeList.at(groupInd).size())
            {
                break;
            }
        }
        if (inGroupInd == codeList.at(groupInd).size())
        {
            groupInd++;
        }
        else
        {
            fruitInd = startFruit+1; // was the way to go, the block underneath doesn't get the job done, when duplicates in the group
        }
    }
    if (groupInd == codeList.size())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    vector<vector<string> > codeList{{"apple", "banana", "apple", "apricot"}, {"anything", "kiwi"}};
    
    vector<string> shoppingCartPass{"guava", "apple", "banana", "apple", "banana", "apple", "apricot", "orange", "banana", "apple", "kiwi", "banana"};
    
    vector<string> shoppingCartFail{"guava", "apple", "banana", "apple", "banana", "apple", "apricot", "orange", "banana", "apple", "banana"};
    
    cout << fruitComparer(shoppingCartPass.at(0), codeList.at(0).at(0)) << endl;
    
    cout << checkWinner(codeList, shoppingCartPass) << endl;
    
    return 0;
}

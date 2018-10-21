// write a function that takes a string of arithmetic equation below and returns a scalar as the evaluation of the equation
// arithmetic supports 4 operators: +, *, &, |, where + and * are defined as usual, & and | are defined as pairwise max, min, respectively. 
// your algorithm should handle space and decimal
// priority: &, | > * > +
// e.g. 1 & 2 | 3 * 4 * 5 + 6
//    = 2 | 3 * 4 * 5 + 6
//    = 2 * 4 * 5 + 6
//    = 46

/*algorithm notes:
- find all spaces, one by one?
  - when found one location, parse string before it to a number (put it in vevtor) and     find operation after it, put in a hash table, with char -> vector indices of order     of operation

- loop each operator 
  - using hash, find the numbers before and after - OPERATE -> then change both 
    numbers to the found number (THIS IS KEY so that next operations can find it)
  - TOWARDS END OF IMPLEMENTATION, FOUND BUGS THAT SHOWED SIMPLY OVER WRITTING CHILDREN PARSED NUMBERS WOULD HAVE WORKED - SO  I HAD TO IMPLEMENT TREE AND RUN ALGORITHM IN O(Q LOG Q) WHERE Q IS THE NUMBER OF OPERATIONS, AS OPPOSED TO O(Q) IMPLEMENTATION (THIS IS WHY I RAN OVER TIME)
  - FINAL ALGORITHM IS O(N + Q LOG Q) WHERE N IS SIZE OF STRING AND Q IS NUMBER OF OPERATIONS
    
- no, maybe more effiient to store all operators in a string, and loop through each in the priority order and find location (actually no - going back to first option)
  - when found, go over one space, find first space, parse number
  - similarly, go back one psace, find last space, parse number and operate!
  
  - instead of chaging the string, which can be O(n) operation, due to resizeing
  - hash the answer with key
  
  - no this algorithm becomes convoluted 
  - also finding each operator from the whole string will be O(k n), better to go back to original idea, to parse whole string first (loop back to first idea)


    
- use operator method for sure!
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;


class ParsedNum
{
  public:
    float number; // may be overflow for corner case, since the input is a string, which can represent a number or arbitrary long size
    ParsedNum* answerNumber;
  
  public:
  // you also need to give default constructor if you are providing constructor. This one is not default constructor
    ParsedNum(float inNumber)
    {
      number = inNumber;
      answerNumber = NULL; // nullptr instead of NULL
    }
  
    float operator&(const ParsedNum &parsedNum)
    {
		// This operator is wrong, the return type should be ParsedNum, not float 
		// a = b & c, a, b, c should all be ParsedNum, right?
		// Same comments for operator | * +
      if (number > parsedNum.number)
      {
        return number;
      }
      else
      {
        return parsedNum.number;
      }
    }
  
    float operator|(const ParsedNum &parsedNum)
    {
      if (number < parsedNum.number)
      {
        return number;
      }
      else
      {
        return parsedNum.number;
      }
    }
  
    float operator+(const ParsedNum &parsedNum)
    {
      return number + parsedNum.number;
    } 
  
    float operator*(const ParsedNum &parsedNum)
    {
      return number * parsedNum.number;
    }
  
    void setAnswerNumber(float inNumber)
    {
      number = inNumber;
    }
    
    ~ParsedNum()
    {
        delete answerNumber;
    }
};

void parseWholeString(string strArithmetic, vector<ParsedNum> &allNumbers, unordered_map<char, vector<int> > &operatorOrderHash, unordered_map<char, int> &operatorCounter, int &numberOfOperators)
{
  size_t found = strArithmetic.find(' ');
  size_t prevFound = 0;
  int foundOperator = 0;
  
  string::size_type sz;
  
  while (found!=std::string::npos)
  {
    //cout << strArithmetic[found+1] << endl;
    int operatorCount = operatorCounter[strArithmetic[found+1]]; // finding how many operator already exists 
	// one line should not exceeds 80 characters, including comments
    operatorOrderHash[strArithmetic[found+1]].at(operatorCount) = foundOperator+1; // storing order of operator in string
    operatorCounter[strArithmetic[found+1]] = operatorCount+1;
    
    //cout << "found " << found << endl;
    //cout << "prevFound " << prevFound << endl;
    //cout << strArithmetic.substr(prevFound, found-prevFound) << endl;
	// I doulbe here there is no space [prevFound, found-prevFound]
	// This problem is very hard, I think, since there are so many corner cases, unless the input is guaanteed to be valid
	// what if input is "abc * xyz", "12.4 5 * 236.7.8"
	// stod instead of stof maybe?
    float parsedNumber = stof(strArithmetic.substr(prevFound, found-prevFound), &sz);
    
    ParsedNum parsedNum(parsedNumber);
    
    allNumbers[foundOperator] = parsedNum;
    
    
    
    prevFound = found+3;
    foundOperator += 1;
    found = strArithmetic.find(' ', found+3); // go to the next space
  }
  float lastNumber = stof(strArithmetic.substr(prevFound, std::string::npos-prevFound), &sz);
  ParsedNum lastParsedNum(lastNumber);
  allNumbers[foundOperator] = lastParsedNum;
  numberOfOperators = foundOperator;
  //cout << allNumbers[foundOperator] << endl;
  //vector<int> testVec = operatorOrderHash['*'];
  //cout << operatorCounter['*'] << endl;
  //cout << testVec[0] << endl;
  //cout << testVec[1] << endl;
  
  //cout << allNumbers << endl;
}

float operateParsedString(int numberOfOperators, vector<ParsedNum> &allNumbers, unordered_map<char, vector<int> > &operatorOrderHash, unordered_map<char, int> &operatorCounter, string &strOperatorOrder)
{
  // the last operation done should be the answer, keep storing it 
  float operatorAnswer = 0;
  vector<int> operatorOrder;
  int operatorCount = 0;
  
  /*int ind = 0;
  while (ind < numberOfOperators+1)
  {
    ParsedNum* dummyChild = new ParsedNum(allNumbers[ind].number);
    allNumbers[ind].answerNumber = dummyChild;
    allNumbers[ind+1].answerNumber = dummyChild;
    ind++;
  }*/
  
  //cout << "before " << endl;
  //cout << allNumbers[1].number << endl;
  //cout << allNumbers[1].answerNumber->number << endl;
  
  // unsigned int --> size_t, use default iterator
  for (unsigned int operatorI = 0; operatorI < strOperatorOrder.length(); operatorI++)
  {
    operatorOrder = operatorOrderHash[strOperatorOrder[operatorI]];
    operatorCount = operatorCounter[strOperatorOrder[operatorI]];
    
    for (int operatorNum = 0; operatorNum < operatorCount; operatorNum++)
    {
      ParsedNum& leftNum = allNumbers[operatorOrder[operatorNum]-1];
      ParsedNum& rightNum = allNumbers[operatorOrder[operatorNum]];
      
      ParsedNum* childLeftNum = &leftNum; 
      ParsedNum* childRightNum = &rightNum;
      
      // finding the children
      while (childLeftNum->answerNumber != 0)
      {
        childLeftNum = childLeftNum->answerNumber;
      }
      while (childRightNum->answerNumber != 0)
      {
        childRightNum = childRightNum->answerNumber;
      } 
      
      if (strOperatorOrder[operatorI] == '&')
      {
        operatorAnswer = (*childLeftNum) & (*childRightNum);
        cout << operatorAnswer << endl;
      }
      else if (strOperatorOrder[operatorI] == '|')
      {
        operatorAnswer = (*childLeftNum) | (*childRightNum);
        cout << operatorAnswer << endl;        
      }
      else if (strOperatorOrder[operatorI] == '+')
      {
        operatorAnswer = (*childLeftNum) + (*childRightNum);
        cout << operatorAnswer << endl;        
      }
      else if (strOperatorOrder[operatorI] == '*')
      {
        operatorAnswer = (*childLeftNum) * (*childRightNum);
        cout << operatorAnswer << endl;         
      }
      
      // adding a new leaf node
	  // whenever there is a new, there should be a delete
	  // You should use smart pointer, unique_ptr, shard_ptr, instead of raw pointer (in real practice)
      ParsedNum* childAnswer = new ParsedNum(operatorAnswer);
      childLeftNum->answerNumber = childAnswer;
      childRightNum->answerNumber = childAnswer; 
      
      // HADN'T PLANNED ON USING A TREE, THOUGHT COULD HAVE OVER WRITTEN THE POINTS AND KEPT ONE CHILD PER PARSED NUMBER -> BUT RUN INTO BUGS
    
    }
  }
  return operatorAnswer;
}

// To execute C++, please define "int main()"
int main() {
  auto words = { "Hello, ", "World!", "\n" };
  for (const string& word : words) {
    cout << word;
  }
  
  // testing...
  /*string test = "&";
  char charT = test[0];
  cout << (charT == '&') << endl;*/
    
  
  string orbits ("686.97 365.24");
  string::size_type sz;     // alias of size_t

  float mars = stof (orbits,&sz);
  cout << mars << endl;
  
  //resultN = mars & 2;
  //cout << resultN << endl;
  
  //ParsedNum parsedNum(mars);
  
  //string inputTest = "1 & 2 | 3 * 4 * 5 + 6";
  string inputTest = "4 + 1 & 2 * 7 | 3 + 6";
  
  ParsedNum parsedNum(0);
  vector<ParsedNum> allNumbers(inputTest.length(), parsedNum); // safe initialization in terms of size, don't want to resize
  
  typedef unordered_map<char, vector<int> > operatorMap;
  typedef unordered_map<char, int > operatorCountMap;
  
  operatorMap operatorOrderHash;
  vector<int> operatorOrders(inputTest.length()); // safe initialization in terms of size, don't want to resize
  operatorOrderHash['&'] = operatorOrders;
  operatorOrderHash['|'] = operatorOrders;
  operatorOrderHash['+'] = operatorOrders;
  operatorOrderHash['*'] = operatorOrders;
  
  operatorCountMap operatorCounter;
  operatorCounter['&'] = 0;
  operatorCounter['|'] = 0;
  operatorCounter['+'] = 0;
  operatorCounter['*'] = 0;
  
  int numberOfOperators = 0;
  parseWholeString(inputTest, allNumbers, operatorOrderHash, operatorCounter, numberOfOperators);
  
  string operatorOrder = "&|*+";
  float answer = operateParsedString(numberOfOperators, allNumbers, operatorOrderHash, operatorCounter, operatorOrder);
  
  cout << endl;
  cout << answer << endl;
  
  
  return answer;
}

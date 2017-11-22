#include <cstdio>
#include "fsm.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace fsm;
using namespace std;

template<typename _T>
void display(vector<_T>& v)
{
  for(const auto& ele : v)
      cout << ele << " ";
  cout << endl;
}

int main(int argc, char** argv)
{
  if(argc == 1)
    {
      cout << "A test filename is needed" << endl;
      return 0;
    }
  
  
  char index;
  FSM<char, bool, int> machine;
  //Set 24 working states, 1 init state.
  machine.setState('0', false);
  for(index = 'a'; index <= 'x'; ++index)
    {
      machine.setState(index, false);
    }
  machine.setState('x', true);

  //23 states
  machine.setTrans('0', 0, 'a');
  machine.setTrans('0', 1, 'a');
  for(index = 'a'; index <= 'w'; ++index)
    {
      machine.setTrans(index, 1, index + 1);
      machine.setTrans(index, 0, 'x');
    }
  machine.setTrans('x', 0, 'a');
  machine.setTrans('x', 1, 'a');
  
  
  cout << "Current state = " << machine.getCurrState() << endl;
  machine.setCurrState('0');
  cout << "Current state = " << machine.getCurrState() << endl;

  //Test file
  string test_str;
  int test_byte;
  vector<int> test_stream;
  vector<char> test_states;
  vector<bool> test_outputs;

  istringstream iss;  
  ifstream ifs(argv[1]);
  while(getline(ifs, test_str))
    {
      test_stream.clear();
      test_states.clear();
      test_outputs.clear();
      
      iss.clear();
      iss.str(test_str);
      
      while(iss >> test_byte)
	test_stream.push_back(test_byte);

      
      for(int byte : test_stream)
	{
	  machine.transit(byte);
	  test_states.push_back(machine.getCurrState());
	  test_outputs.push_back(machine.getCurrOutput());
	}

      //Show result
      cout << endl;
      display<int>(test_stream);
      display<char>(test_states);
      display<bool>(test_outputs);
    }

  return 0;
}

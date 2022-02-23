/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Andrew Narvaez and Michael Bearint
 * Date        : 11 November 2021
 * Description : A program to solve the famous water jug puzzle using breadth-first search in C++.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
        
    int a, b, c;
    string directions;
    State *parent; 
    
	  State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {};

    State(int _a, int _b, int _c,string _d,  State *p) : 
        a{_a}, b{_b}, c{_c}, directions{_d}, parent{p} { };
    
    int geta(){
        return a;
    };
    int getb(){
        return b;
    };
    int getc(){
        return c;
    };
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    };
};

//print recursively to print initial node first
void printSteps(State solution){
  if(solution.parent != NULL){
    //recursive print function
    printSteps(*solution.parent);
  }
  cout << solution.directions << " " << solution.to_string() << endl;
}
  
State search(int a, int b, int c, int goalA, int goalB, int goalC){
		//initialize queue and start state
		queue<State> states;
		states.push(State(0,0,c, "Initial state.", NULL));


		//create 2d array(using vectors) of already visited states.
		//vector<vector<bool>> alreadyVisited(a + 1, vector<bool> (b+1,false));

    // Declare a 2D array with 'some_size' rows.
    bool **array = new bool*[a+1];
    // For each row, make an array of 'some_other_size' booleans.
    for(int i = 0; i < a+1; i++) {
      array[i] = new bool[b+1];
      // Initialize the new row.
      fill(array[i], array[i] + b+1, false);
    }

		State *current;

		while(!states.empty()){              
			current = new State(states.front());
			states.pop();
      
      //Checks if current equals goal_state and returns the solution if it does
      if(current->geta() == goalA && current->getb() == goalB && current->getc() == goalC){ //THIS IS WRONG------------------------------------------
          printSteps(*current);
          State solution = *current;
          delete current;

        //DELETE ARRAY
        for(int i =0; i < b+1; i++){
          delete [] array[i];
        }
        delete [] array;
        return solution;
      }

      
      //Checks if current has already been seen TODO
      if(array[current->geta()][current->getb()]){
				 continue;
      } else{
    	  array[current->geta()][current->getb()] = true;
      }
      
      int poured;

      //---------------------------------------------------------------
      //1)Pour from C to A
      if(current->getc() != 0 && current-> a != a){
          poured = a - current->a;
          string flag = (poured == 1) ? "" : "s";
		  string flag_curr = (current->c == 1) ? "" : "s";
	

          if(poured >= current->c){
            states.push(State(current->a + current->c, current->b, 0, "Pour " + to_string(current->c) + " gallon" + flag_curr + " from C to A.", current));
          } else{
            states.push(State(a, current->b, current->c - poured, "Pour " + to_string(poured) + " gallon" + flag + " from C to A.", current));
          }
      }
      //---------------------------------------------------------------------------------------------------------------------------------------------
      //2)Pour from B to A
      if(current->getb() != 0 && current-> a != a){
        poured = a - current->a;
        string flag = (poured == 1) ? "" : "s";
		  string flag_curr = (current->b == 1) ? "" : "s";
          
        if(poured >= current->b){
           states.push(State(current->a + current->b, 0, current->c, "Pour " + to_string(current->b) + " gallon" + flag_curr + " from B to A.", current));
        } else{
          states.push(State(a, current->b - poured, current->c, "Pour " + to_string(poured) + " gallon" + flag + " from B to A.", current));
        }
      }

      //--------------------------------------------------------------------------------------------------------------------------------------------
      //3)Pour from C to B
      if(current->getc() != 0 && current-> b != b){
          poured = b - current->b;  
          string flag = (poured == 1) ? "" : "s";
		  string flag_curr = (current->c == 1) ? "" : "s";
          if(poured >= current->c){
            states.push(State(current->a, current->b + current->c, 0, "Pour " + to_string(current->c) + " gallon" + flag_curr + " from C to B.", current));
          } else{
            states.push(State(current->a, b, current->c - poured, "Pour " + to_string(poured) + " gallon" + flag + " from C to B.", current));
          }

      }
      
      //---------------------------------------------------------------------------------------------------------------------------------------------
      //4)Pour from A to B
      if(current->getb() != b && current-> a != 0){
        poured = b - current->b;  
        string flag = (poured == 1) ? "" : "s";
		  string flag_curr = (current->a == 1) ? "" : "s";
        if(poured >= current->a){
          states.push(State(0, current->b + current->a, current->c, "Pour " + to_string(current->a) + " gallon" + flag_curr + " from A to B.", current));
        } else{
          states.push(State(current->a - poured, b, current->c, "Pour " + to_string(poured) + " gallon" + flag + " from A to B.", current));
        }

      }

      //---------------------------------------------------------------
      //5)Pour from B to C
      if(current->getb() != 0 && current-> c != c){
        poured = c - current->c;  
          string flag = (poured == 1) ? "" : "s";
		  string flag_curr = (current->b == 1) ? "" : "s";

          if(poured >= current->b){
            states.push(State(current->a, 0, current->c + current->b, "Pour " + to_string(current->b) + " gallon" + flag_curr + " from B to C.", current));
          } else{
            states.push(State(current->a, current->b - poured, c, "Pour " + to_string(poured) + " gallon" + flag + " from B to C.", current));
          }

      }

      //---------------------------------------------------------------
      //6)Pour from A to C
      if(current->geta() != 0 && current-> c != c){
          poured = c - current->c;  
          string flag = (poured == 1) ? "" : "s";
		  string flag_curr = (current->a == 1) ? "" : "s";

          if(poured >= current->a){
            states.push(State(0, current->b, current->c + current->a, "Pour " + to_string(current->a) + " gallon" + flag_curr + " from A to C.", current));
          } else{
            states.push(State(current->a - poured, current->b, c, "Pour " + to_string(poured) + " gallon" + flag + " from A to C.", current));
          }
      }
    }
	cout << "No solution.";
    return State(-1,-1,-1);
}






int main(int argc, char * const argv[]) {

	//Creation of input array... values are as follows
	//0, capA, capB, capC, goalA, goalB, goalC;
	int input[7] = {0,0,0,0,0,0,0};

	//Error testing for erroneous input
	istringstream iss;
	if(argc != 7){
		cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return 1;
	}
	char letter[7] = {' ', 'A', 'B', 'C', 'A', 'B', 'C'};
	for(int i = 1; i < 7; i++){
		int value = 0;
		iss.str(argv[i]);
		if(!(iss >> value)){
			if(i<4){
				cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << letter[i] << "." << endl;
			} else{
				cerr << "Error: Invalid goal '" << argv[i] <<"' for jug " << letter[i] << "." << endl;
			}
			return 1;
		}
		if(value <= 0 && i < 4){
			cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << letter[i] << "." << endl;
			return 1;
		} else if(value<0){
			cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << letter[i] << "." << endl;
			return 1;
		}
		//Sets input if good...
		input[i] = value;
		iss.clear();
	}

	//Error testing for illogical input
	for(int i = 1; i < 4; i++){
		if(input[i] < input[i+3]){
			cerr << "Error: Goal cannot exceed capacity of jug " << letter[i] << "." << endl;
			return 1;
		}
	}

	if(input[4] + input[5] + input[6] != input[3]){
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." <<endl;
		return 1;
	}

  State ans = search(input[1],input[2],input[3],input[4],input[5],input[6]);

  return 0;
}




/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Michael Bearint
 * Version : 1.0
 * Date    : September 1, 2021
 * Description : Computes the square root of the command-line argument.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/


#include <iostream>
#include <sstream>
#include <limits>
#include <iomanip>

using namespace std;

double sqrt(double num, double epsilon){
    double nextGuess;
    double lastGuess = num;
	if(num < 0){
        return numeric_limits<double>::quiet_NaN();
    }
    if(num == 0){
        return num;
    }
    if(num == 1){
        return num;
    }
    //infinite loop until root is found, then a break
    int infinite = 1;
    while(infinite > 0){
        nextGuess = (lastGuess +(num/lastGuess))/2;
        if(abs(lastGuess-nextGuess) <= epsilon){
            break;
        }
        lastGuess=nextGuess;
    }
    return nextGuess;
}


int main(int argc, char* argv[]){
	double m;
    double n;
	istringstream iss;
	
	if (argc >3 || argc <=1){
		cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
		return 1;
	}
    if(argc == 3){
	    iss.str(argv[1]);
	    if(!(iss >> m)){
	    cerr << "Value argument must be a double." << endl;
	    return 1;
	    }

	    iss.clear();

	    iss.str(argv[2]);
	    if(!(iss >> n)){
	    cerr << "Error: Epsilon argument must be a positive double." << endl;
	    return 1;
	    }
    }
    if(argc == 2){
	    iss.str(argv[1]);
	    if(!(iss >> m)){
	    cerr << "Error: Value argument must be a double." << endl;
	    return 1;
	    }

        n = 1e-7;
    }
    if(n <= 0){
        cerr << "Error: Epsilon argument must be a positive double.";
        return 1;
    }

    double squareRoot = sqrt(m,n);

	cout << fixed << setprecision(8) << squareRoot << endl;

	
	return 0;
}